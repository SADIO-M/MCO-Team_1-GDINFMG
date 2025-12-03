# MCO-Team_1-GDINFMG
The repository for the application code of Team 1's MCO GDINFMG XX22

[!!] APPLICATION SET UP INSTRUCTIONS:
1. Build as Release x64
2. Go to C/C++
  - General
      - Additional Include Libraries: $(SolutionDir)Dependencies\include\jdbc;%(AdditionalIncludeDirectories)
  - Preprocessor
      - Preprocessor Definitions: STATIC_CONCPP;NDEBUG;_CONSOLE;%(PreprocessorDefinitions)
3. Linker
  - General
      - Additional Library Dependencies: $(SolutionDir)Dependencies\lib64\vs14;%(AdditionalLibraryDirectories)
  - Input
       - Additional Dependencies: mysqlcppconn-static.lib;%(AdditionalDependencies)