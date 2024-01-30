# SENTIMENT ANALYSIS TEXT CLASSIFICATION AND MODEL COMPARISON WITH MLPACK C++

---

## COMMIT IN-DEPTH DESCRIPTION

- Added [removestopwords method](./Model/ModelFlow/src/Preprocessing.cpp)
- Added more functıons in [StringManipulation.hpp](./Model/ModelFlow/include/StringManipulation.hpp)
- Added a text file that contains the [characters](./Model/ModelFlow/configs/removechars.txt) to exclude
  > Then after doing this i just found out that c++ has a function that removes punctuations -\_-!
- Added [stopwords](./Model/ModelFlow/configs/stopwords.txt) in a text file
- Added more includes to [ModelFlow.hpp](./Model/ModelFlow/include/ModelFlow.hpp)

## Discussions and insights

- should i remove the Json Dataset private member from the Preprocessor class?
  > well i am not using RAM, just file system and it was there at first for holding the dataset in RAM _Bad idea_...
- I should remember to add error handling, but that will be later...

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
