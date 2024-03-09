# SENTIMENT ANALYSIS TEXT CLASSIFICATION AND MODEL COMPARISON WITH MLPACK C++

---

## COMMIT IN-DEPTH DESCRIPTION

- added [modelbuild](./Model/ModelFlow/include/ModelBuild.hpp) and its [implementation file](./Model/ModelFlow/src/ModelBuild.cpp)


## Discussions and insights

- should i remove the Json Dataset private member from the Preprocessor class?
  > well i am not using RAM, just file system and it was there at first for holding the dataset in RAM _Bad idea_...
- I should remember to add error handling, but that will be later...
- Thinking whether to use sparse matrix or normal matrix; sparse matrix is more memory efficient but slower
  > Many functions arent supported with sparse matrix so normal matrix it is
  > Next is memory issues, hmmm
- would try savıng the matrıxes ın bınary format or csv
- modified [preprocessor combine method](./Model/ModelFlow/include/Preprocessing.hpp) to support collecting a specific file from the cloud
  > the file uri will be added later

- ### Currently on building it with a non NN model

* Logistic regression
* Linear SVM
* Random forest
* Naive bayes

- ### Evaluation units
- Accuracy
- Precision
- F1 score
- Recall
- Support

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
- [x] Convert the downloaded datasets into a useable formaT
- [x] Build the Preprocessor Class
- [x] Save the preprocessed datasets
- [x] Vectorize the datasets for ML algorithms
- - [x] Test the String encoding policies of Mlpack
- - [x] Test the Scalar methods
- [ ] Train a classification model
- [ ] Evaluate the classification model
- [ ] Train a test model
- [ ] Evaluate the test model
- [ ] Save the model
- [ ] Build uWebSockets server
- [ ] Test server
- [ ] Build the server with model hosting capabilities
- [ ] Add the specific file download uri

## REFERENCES

-_This list contains where ideas were also pulled from_-

- placeholder

---

## Disclaimer

Everything written in this file is subject to change on every git commit
