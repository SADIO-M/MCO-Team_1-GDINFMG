# MCO-Team_1-GDINFMG
The repository for the application code of Team 1's MCO GDINFMG XX22

[!!] SOFTWARE NEEDED:
- Visual Studio
- MySQL

[!!] APPLICATION SET UP INSTRUCTIONS:
You may view this Google Docs link for visuals and instructions on how to build the application: https://docs.google.com/document/d/1tBAdwughnEzeFVVecsYV7nl9D5ryW-PghzBTyTNQSbk/edit?usp=sharing

The instructions seen above are also written here:
1. Build as Release x64
2. At the top bar, click on "Project", then click on to MCO-Team-1-TRPG Properties. A window should pop up.
3. Navigate to C/C++
  3.a Go to "General"
      - Click on the text box beside Additional Include Directories and copy paste this: $(SolutionDir)Dependencies\include\jdbc;%(AdditionalIncludeDirectories)
  3.b Go to "Preprocessor"
      - Click on the text box beside Preprocessor Definitions and copy paste this: STATIC_CONCPP;NDEBUG;_CONSOLE;%(PreprocessorDefinitions)
4. Navigate to Linker
  4.a Go to "General"
      - Click on the text box beside Additional Library Directories and copy paste this: $(SolutionDir)Dependencies\lib64\vs14;%(AdditionalLibraryDirectories)
  4.b Go to "Input"
      - Click on the text box beside Additional Dependencies and copy paste this: mysqlcppconn-static.lib;%(AdditionalDependencies)
5. Build the solution and run.
6. View available Game Master IDs below to input as User ID.

[!!] AVAILABLE GAME MASTER IDs: 
    - 50001 (RECOMMENDED)
    - 50002
    - 50003

[!!] REMINDERS:
1. The "server password" that the application requests for when you run it is the password you set when creating the local host that has the database.