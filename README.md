# SENTIMENT ANALYSIS TEXT CLASSIFICATION AND MODEL COMPARISON WITH MLPACK C++

---

# COMMIT IN-DEPTH DESCRIPTION

- Added [parser python Script](./Model/ModelFlow/data/parser.py)
  The requirements.txt for the python script is also available
  The parser.py converts .txt.gz files into .json files
  It accepts two arguments; inputfile path and outputfile path

## Project Tree:

-_subject to change on every commit_-

```
 ./
 ├── Documents/
 │  └── ...
 ├── Model/
 │  ├── .devcontainer
 │  ├── MLServer/
 │  │  ├── config/
 │  │  ├── build/
 │  │  ├── include/
 │  │  ├── lib/
 │  │  ├── src/
 │  │  ├── out/
 │  │  │  ├── Models/
 │  │  │  └── ...
 │  │  ├── README.md
 │  │  ├── install.sh
 │  │  └── CMakeLists.txt
 │  ├── ModelFlow/
 │  │  ├── build/
 │  │  ├── include/
 │  │  ├── lib/
 │  │  ├── src/
 │  │  ├── out/
 │  │  │  ├── Data/
 │  │  │  ├── Models/
 │  │  │  └── ...
 │  │  ├── README.md
 │  │  └── CMakeLists.txt
 │  └── README.md
 ├── Server/
 │  └── ...
 ├── LICENSE
 └── README.md
```

---

## TOOLS, FRAMEWORKS, LIBRARIES

- Docker
- Cmake
- uSockets
- uWebSockets
- Mlpack
- C++
- Visual Studio Code
- PostgreSQL
- Fl0.com

## TODO:

-_subject to change on every commit_-

- [ ] Download the datasets
- [ ] Convert the downloaded datasets into a useable formaT
- [ ] Build the Preprocessor Class
- [ ] Save the preprocessed datasets
- [ ] Vectorize the datasets for ML algorithms
- - [ ] Test the String encoding policies of Mlpack
- - [ ] Test the Scalar methods
- [ ] Train a classification model
- [ ] Evaluate the classification model
- [ ] Train a test model
- [ ] Evaluate the test model
- [ ] Save the model
- [ ] Build uWebSockets server
- [ ] Test server
- [ ] Build the server with model hosting capabilities

## REFERENCES

-_This list contains where ideas were also pulled from_-

- placeholder

---

## Disclaimer

Everything written in this file is subject to change on every git commit
