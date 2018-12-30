# Sudoku

* **Read me first**


* It's a project for solving Sudoku games and creating Sudoku solutions automatically.
* The project is based on `64-bit Windows` and `Visual Studio 2017` / `Mingw`. `Linux` and `macOS` are not currently supported.

#### Directory

```
bin/
    Sudoku.exe                          Binary executable for Windows x64
src/                                    
    Sudoku-for-VS.cpp                   Main function for Visual Studio
    Sudoku-for-Mingw.cpp                Main function for Mingw
    Sudoku.h                            Header file 
    lib/                                
        dlx.hpp                         Components for calculation
        fastIO.hpp                      Components for faster input/output
test/                                   
    assert_1.exe                        Assert whether '-c' operation is non-repeating
    assert_1.cpp                        Source code for assert_1.exe/Based on Mingw & c++11
    assert_2.exe                        Assert whether '-c/-s' operation gets valid solution
    assert_2.cpp                        Source code for assert_2.exe/Based on Mingw & c++11
    gen.exe                             Generate 100000 same Sudoku for testing '-s' speed
    gen.cpp                             Source code for gen.exe/Based on Mingw & c++11
    unittest1.cpp                       Unit test code
    testcase_1.txt                      Constructed correct data for testing '-s' correctness
    testcase_2.txt                      Constructed wrong data for testing '-s' correctness
    testcase_3.txt                      Constructed wrong data for testing '-s' correctness
    testcase_4.txt                      Constructed wrong data for testing '-s' correctness
docs/                                   
    设计文档.docx                        Design document of the project (not in English)
    测试文档.docx                        Testing document of the project (not in English)
```

#### Compile & Run

* If you don't want to use the binary executable `bin/Sudoku.exe` , you can compile and generate a new  binary executable. Two ways supported: `Visual Studio` and `Mingw` , both in `Windows x64`.
  * For `Visual Studio`:
    * Create a project anywhere you like.
    * Replace the main file with `Sudoku-for-VS.cpp` and copy folder`lib/`to this place.
    * Generate binary executable.
  * For `Mingw`
    * Change present working directory to `src\`.
    * Execute`g++ -Wall -std=c++11 -O2 -o ../bin/Sudoku-Mingw.exe Sudoku-for-Mingw.cpp `.
    * Find new binary executable in `bin/`.
* Two parameters for `bin/Sudoku.exe`: 
  * First, operation type is needed. It can be `-c`/`-C` /`-s`/`-S`. It's not case sensitive.
  * Second, if operation is `-c`/`-C`, a number `n` is needed. It should be the number of distinct Sudoku. If operation is `-s`/`-S`, a file path (absolute or relative) is needed.  It should be the file path of the input Sudoku file.
    * If the program run to the end, it will output the data into `sudoku.txt` in relative path.
* No parameters for `test/gen.exe`. It will generate an input file of 100000 same Sudoku `sudoku.in` in relative path for `-s` operation.
* One parameter for `test/assert.exe`: the file path of an output of `-c` operation. It will check if an output of `-c` is non-repeating. If some Sudoku are not distinct, it will show an `assertion fail`.


####For more info, read the related blog that introduces this project:  [Blog](https://www.cnblogs.com/zhber/p/10016909.html)

