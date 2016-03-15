package com.janitovff.opencl2cplugin

import org.gradle.api.DefaultTask
import org.gradle.api.tasks.incremental.IncrementalTaskInputs
import org.gradle.api.tasks.InputDirectory
import org.gradle.api.tasks.OutputDirectory
import org.gradle.api.tasks.TaskAction

public class OpenCL2CTask extends DefaultTask {
    @InputDirectory
    def File inputDirectory

    @OutputDirectory
    def File outputDirectory

    @TaskAction
    void execute(IncrementalTaskInputs inputs) {
        if (!inputs.incremental)
            project.delete(outputDirectory.listFiles())

        inputs.outOfDate { change ->
            def targetFileName = getTargetFileName(change.file.name)
            def targetName = getTargetName(change.file.name)
            def targetFile = getTargetFile(targetFileName)
            def headerGuard = getTargetHeaderGuard(targetFileName)
            def sourceCode = change.file.text

            targetFile.text = stringify(headerGuard, targetName, sourceCode)
        }

        inputs.removed { change ->
            def targetFile = getTargetFile(change.file.name)

            targetFile.delete()
        }
    }

    File getTargetFile(String targetFileName) {
        return new File(outputDirectory, targetFileName)
    }

    String getTargetFileName(String sourceFileName) {
        return sourceFileName.replaceAll("\\.cl\$", ".h")
    }

    String getTargetName(String sourceFileName) {
        return sourceFileName.replaceAll("\\.cl\$", "SourceCode");
    }

    String getTargetHeaderGuard(String targetFileName) {
        def guard = new StringBuilder()
        def fileNameSize = targetFileName.length()

        guard.append(Character.toUpperCase(targetFileName.charAt(0)))

        for (int index = 1; index < fileNameSize; ++index) {
            def currentChar = targetFileName.charAt(index)

            if (Character.isUpperCase(currentChar))
                guard.append('_')
            else if (!Character.isJavaIdentifierPart(currentChar))
                currentChar = '_'
            else
                currentChar = Character.toUpperCase(currentChar)

            guard.append(currentChar)
        }

        return guard.toString()
    }

    String stringify(String headerGuard, String targetName, String sourceCode) {
        def output = new StringBuffer()

        output.append("#ifndef ")
        output.append(headerGuard)
        output.append("\n#define ")
        output.append(headerGuard)

        output.append("\n\nconst char ")
        output.append(targetName)
        output.append("[] = \n\n\"")

        output.append(sourceCode
            .replaceAll("\\\\", "\\\\\\\\")
            .replaceAll("\"", "\\\\\"")
            .replaceAll("\n", "\\\\n\"\n\""))

        output.append("\";\n\n")

        output.append("#endif\n")

        return output.toString()
    }
}
