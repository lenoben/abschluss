# SENTIMENT ANALYSIS TEXT CLASSIFICATION AND MODEL COMPARISON WITH MLPACK C++

---

## COMMIT IN-DEPTH DESCRIPTION

- added my implementation of knn
- added [K-Nearest Neigbour KNN](./Model/ModelFlow/include/mein_knn.hpp)
- added [implementation of KNN](./Model/ModelFlow/src/mein_knn.cpp)


## Discussions and insights

- should i remove the Json Dataset private member from the Preprocessor class?
  > well i am not using RAM, just file system and it was there at first for holding the dataset in RAM _Bad idea_...

  _-removed-_
- I should remember to add error handling, but that will be later...
- I should remember to add doxygen comments
- Thinking whether to use sparse matrix or normal matrix; sparse matrix is more memory efficient but slower
  > Many functions arent supported with sparse matrix so normal matrix it is
  > Next is memory issues, hmmm
- would try savıng the matrıxes ın bınary format or csv
- modified [preprocessor combine method](./Model/ModelFlow/include/Preprocessing.hpp) to support collecting a specific file from the cloud
  > the file uri will be added later

- ### Currently building models

* Logistic regression
* Linear regression (possible)
* Linear SVM 🚫
* Random forest
* Naive bayes 🚫
* Self made KNN
* Self made nearest mean classifier NMC
* FFN

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
- Render.com
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
- [x] Train a classification model
- [x] Evaluate the classification model
- [x] Train a test model
- [x] Evaluate the test model
- [x] Save the model
- [x] Build uWebSockets server
- [x] Test server
- [x] Build the server with model hosting capabilities
- [ ] Add the specific file download uri

## REFERENCES

- [Porter stemmer algorithm](https://tartarus.org/martin/PorterStemmer/)

---

## Disclaimer

Everything written in this file is subject to change on every git commit
