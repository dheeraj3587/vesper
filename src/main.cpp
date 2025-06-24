#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include "Lexer.h"
#include "Parser.h"
#include "AST.h"
#include "CodeGen.h"

void printUsage(const char *programName)
{
    std::cout << "Usage: " << programName << " [options] <file.vsp>\n";
    std::cout << "Options:\n";
    std::cout << "  -o <output>    Specify output file name (default: program)\n";
    std::cout << "  -S             Generate assembly only (don't create binary)\n";
    std::cout << "  -c             Compile to object file only\n";
    std::cout << "  -v, --verbose  Verbose output\n";
    std::cout << "  -h, --help     Show this help message\n";
    std::cout << "\nExamples:\n";
    std::cout << "  " << programName << " program.vsp              # Compile to 'program' binary\n";
    std::cout << "  " << programName << " -o myapp program.vsp     # Compile to 'myapp' binary\n";
    std::cout << "  " << programName << " -S program.vsp           # Generate assembly only\n";
}

int main(int argc, char *argv[])
{
    std::string inputFile;
    std::string outputFile = "program";
    bool assemblyOnly = false;
    bool objectOnly = false;
    bool verbose = false;

    // Parse command line arguments
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
        {
            outputFile = argv[++i];
        }
        else if (strcmp(argv[i], "-S") == 0)
        {
            assemblyOnly = true;
        }
        else if (strcmp(argv[i], "-c") == 0)
        {
            objectOnly = true;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
        {
            verbose = true;
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            printUsage(argv[0]);
            return 0;
        }
        else if (argv[i][0] == '-')
        {
            std::cerr << "Unknown option: " << argv[i] << "\n";
            printUsage(argv[0]);
            return 1;
        }
        else
        {
            inputFile = argv[i];
        }
    }

    if (inputFile.empty())
    {
        std::cerr << "Error: No input file specified\n";
        printUsage(argv[0]);
        return 1;
    }

    // Read the input file
    std::ifstream infile(inputFile);
    if (!infile)
    {
        std::cerr << "Error: Could not open file '" << inputFile << "'\n";
        return 1;
    }

    // Read the entire file content
    std::string code((std::istreambuf_iterator<char>(infile)),
                     std::istreambuf_iterator<char>());
    infile.close();

    if (verbose)
    {
        std::cout << "🔍 Compiling: " << inputFile << std::endl;
        std::cout << "📝 Source Code:\n"
                  << code << std::endl
                  << std::endl;
    }

    // 1. Lexing
    Lexer lexer(code);
    std::vector<std::string> tokens;
    try
    {
        tokens = lexer.tokenize();
        if (verbose)
        {
            std::cout << "🔤 Tokens:" << std::endl;
            for (const auto &token : tokens)
            {
                std::cout << "'" << token << "' ";
            }
            std::cout << std::endl
                      << std::endl;
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "❌ Lexer Error: " << e.what() << std::endl;
        return 1;
    }

    if (tokens.empty())
    {
        std::cout << "⚠️  No tokens to parse." << std::endl;
        return 0;
    }

    // 2. Parsing
    Parser parser(tokens);
    if (verbose)
    {
        std::cout << "🔍 Parsing..." << std::endl;
    }

    try
    {
        auto program = parser.ParseProgram();
        if (program)
        {
            if (verbose)
            {
                std::cout << "✅ Successfully parsed program:" << std::endl;
                std::cout << "========================" << std::endl;
                program->print();
                std::cout << "========================" << std::endl;
            }

            // 3. Code Generation
            CodeGen codegen;
            codegen.generateAssembly(program.get());

            std::string asmFile = outputFile + ".asm";
            std::string objFile = outputFile + ".o";

            if (verbose)
            {
                std::string asmCode = codegen.getAssembly();
                std::cout << "\n🔧 Generated Assembly:\n"
                          << asmCode << std::endl;
            }

            // Generate assembly file
            codegen.writeToFile(asmFile);
            std::cout << "📄 Assembly written to " << asmFile << std::endl;

            if (assemblyOnly)
            {
                std::cout << "✅ Assembly generation complete!" << std::endl;
                return 0;
            }

            // Generate binary
            if (verbose)
            {
                std::cout << "🔗 Generating binary..." << std::endl;
            }

            if (codegen.generateBinary(asmFile, outputFile))
            {
                std::cout << "🎉 Binary compilation successful!" << std::endl;
                std::cout << "📦 Executable: " << outputFile << std::endl;

                // Test the binary
                if (verbose)
                {
                    std::cout << "\n🧪 Testing the binary..." << std::endl;
                    std::string testCmd = "./" + outputFile + " && echo \"Exit code: $?\"";
                    std::system(testCmd.c_str());
                }
            }
            else
            {
                std::cerr << "❌ Binary generation failed!" << std::endl;
                return 1;
            }
        }
        else
        {
            std::cerr << "❌ Failed to parse program." << std::endl;
            return 1;
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "❌ Parser Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}