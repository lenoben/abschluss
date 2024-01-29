# SENTIMENT ANALYSIS TEXT CLASSIFICATION AND MODEL COMPARISON WITH MLPACK C++

---

## COMMIT IN-DEPTH DESCRIPTION

- changed an overloaded constructor to take a string copy instead of a string reference [&list -->> list](./Model/ModelFlow/include/Preprocessing.hpp)
  > The reason is due to the fact that i want the list stored inside the class to be dependent from the outside list.
  > Enabling the user to reuse that list variable for something else.
- Added [Combine methods](./Model/ModelFlow/src/Preprocessing.cpp)
  > Still work in progress 🧩
- Added [StringManipulation.hpp](./Model/ModelFlow/include/StringManipulation.hpp)
  > Contains methods/fucntions the preprocessor class will use to manipulate strings
- Added some documentations

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
- Python3

## TODO:

-_subject to change on every commit_-

- [x] Download the datasets
- [ ] Convert the downloaded datasets into a useable formaT
- [x] Build the Preprocessor Class
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
