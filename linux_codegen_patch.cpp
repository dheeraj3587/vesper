// Linux-specific modifications for CodeGen.cpp
// Apply these changes to make the compiler work on Linux

// In CodeGen::assembleToBinary method, replace the macOS-specific code with:

bool CodeGen::assembleToBinary(const std::string &asmFile, const std::string &outputBinary)
{
    std::string objFile = outputBinary + ".o";

// Detect the platform
#ifdef __linux__
    // Linux-specific assembly and linking

    // First, we need to modify the assembly for Linux
    std::string linuxAsmFile = outputBinary + "_linux.asm";
    std::ifstream input(asmFile);
    std::ofstream output(linuxAsmFile);

    std::string line;
    while (std::getline(input, line))
    {
        // Replace _main with main for Linux
        if (line == "global _main")
        {
            output << "global main" << std::endl;
        }
        else if (line == "_main:")
        {
            output << "main:" << std::endl;
        }
        else
        {
            output << line << std::endl;
        }
    }
    input.close();
    output.close();

    // Step 1: Assemble to object file
    std::string nasmCmd = "nasm -f elf64 " + linuxAsmFile + " -o " + objFile;
    std::cout << "Assembling: " << nasmCmd << std::endl;

    int nasmResult = std::system(nasmCmd.c_str());
    if (nasmResult != 0)
    {
        std::cerr << "Error: Assembly failed with nasm" << std::endl;
        std::remove(linuxAsmFile.c_str());
        return false;
    }

    // Step 2: Link to executable (Linux specific)
    std::string linkCmd = "ld -o " + outputBinary + " " + objFile + " -e main";
    std::cout << "Linking: " << linkCmd << std::endl;

    int linkResult = std::system(linkCmd.c_str());
    if (linkResult != 0)
    {
        std::cerr << "Error: Linking failed. Trying alternative approach..." << std::endl;

        // Alternative linking approach for Linux
        std::string altLinkCmd = "gcc -o " + outputBinary + " " + objFile + " -nostdlib -e main";
        std::cout << "Trying: " << altLinkCmd << std::endl;

        linkResult = std::system(altLinkCmd.c_str());
        if (linkResult != 0)
        {
            std::cerr << "Error: Both linking approaches failed" << std::endl;
            std::remove(linuxAsmFile.c_str());
            std::remove(objFile.c_str());
            return false;
        }
    }

    // Clean up temporary files
    std::remove(linuxAsmFile.c_str());
    std::remove(objFile.c_str());

#elif __APPLE__
    // Original macOS code here...
    // (keep the existing macOS implementation)
#else
    std::cerr << "Error: Unsupported platform" << std::endl;
    return false;
#endif

    std::cout << "✅ Binary generated successfully: " << outputBinary << std::endl;
    return true;
}