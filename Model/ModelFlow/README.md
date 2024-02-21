# ModelFlow

This directory houses the codebase for preprocessing, model building, training and evaluation.

## FileFormat during preprocessing

There are 2 major file format, `FileType::TXTGZ` is there if we do not whant to use the python script to parse it into Json, _*Highly not recommended, convert it to Json first then txt*_

- .txt, from converting the `FileType::TXTGZ` to `FileType::TXT`

```
product/productId: B0001DUBWI
product/title: Darice - Alphabet Beads 6mm 160/Pkg
product/price: 5.18
review/userId: A3LILKXIB2TH7N
review/profileName: mrshaggs "Amazon Addict"
review/helpfulness: 2/2
review/score: 5.0
review/time: 1334620800
review/summary: Good Addition to a Bead Kit
```

- .json (multi-object seperated by newlines) from converting the `FileType::TXTGZ` to `FileType::JSON`

```json
{"product/productId": "B000GKXY4S", "product/title": "Crazy Shape Scissor Set", "product/price": "unknown", "review/userId": "A1QA985ULVCQOB", "review/profileName": "Carleen M. Amadio \"Lady Dragonfly\"", "review/helpfulness": "2/2", "review/score": "5.0", "review/time": "1314057600", "review/summary": "Fun for adults too!", "review/text": "I really enjoy these scissors for my inspiration books that I am making"}
{"product/productId": "B000GKXY4S", "product/title": "Crazy Shape Scissor Set", "product/price": "unknown", "review/userId": "ALCX2ELNHLQA7", "review/profileName": "Barbara", "review/helpfulness": "0/0", "review/score": "5.0", "review/time": "1328659200", "review/summary": "Making the cut!", "review/text": "Looked all over in art supply and other stores for \"crazy cutting\""}
{}
```

- .json (singular object)

```json
[
  {
    "product/productId": "B000GKXY4S",
    "product/title": "Crazy Shape Scissor Set",
    "product/price": "unknown",
    "review/userId": "A1QA985ULVCQOB",
    "review/profileName": "Carleen M. Amadio \"Lady Dragonfly\"",
    "review/helpfulness": "2/2",
    "review/score": "5.0",
    "review/time": "1314057600",
    "review/summary": "Fun for adults too!",
    "review/text": "I really enjoy these scissors for my inspiration books that I am making"
  },
  {
    "product/productId": "B000GKXY4S",
    "product/title": "Crazy Shape Scissor Set",
    "product/price": "unknown",
    "review/userId": "ALCX2ELNHLQA7",
    "review/profileName": "Barbara",
    "review/helpfulness": "0/0",
    "review/score": "5.0",
    "review/time": "1328659200",
    "review/summary": "Making the cut!",
    "review/text": "Looked all over in art supply and other stores for \"crazy cutting\""
  },
  {}
]
```

## Smooth preprocessing path

- Get the individual filename with extension on hopefully it is .txt.gz in a list
- initiate a preprocessor class with the list and associated filetype
- convert .txt.gz to json
  > it will produce multiple jsons for each individual files
  > each a **_multi-object separated bt newline_** json file
- combine all the multiple jsons into a single json file, that is an array of objects(singular object)
  > it is quite memory intensive
- convert that combined json into 2 text files that contains just the scores and text
- remove the stopwords from the text file
- remove the unwanted characters from the text file
- divide the text file into into positive and negative text using the score text file
  > you can determine the threshold you want
- make the divided text files equal
- combine the equally divided text files

```cpp
std::vector<std::string> yourlist = {"../data/arts.txt.gz","../data/clothings.txt.gz"};
// init the preprocessor class with filetype
Preprocessor review = Preprocessor(FileType::TXTGZ);
// add your list of .txt.gz
review.addList(yourlist);
// convert the list of .txt.gz to list of .json
review.ConvertTxtgzToJson();
// combine the list of .json into combined.json
review.Combine();
// convert that combined.json into score.txt and text.txt
review.ConvertJsonToTxt();
// removes stopwords from the text.txt or [1], makes score.txt and nostopword.txt
review.removeStopWords();
// removes unwanted characters from [1] or text.tx or nostopword.txt to cleaned.txt
review.removech();
// Takes score.txt and either text.txt or nostopword.txt
// divides it and list is hightext.txt, lowtext.txt
review.dividePostiveandNegative(3);
// output => equalhightext.txt, equallowtext.txt
review.saveEqualdivided();
//
review.Combine();
```

# output.sh

```sh
[INFO]     TXTGZ FileType
[INFO]    [0]    ../data/raw/Arts
[INFO]    [1]    ../data/raw/Automotive
[INFO]    [2]    ../data/raw/Cell_Phones
[INFO]    [3]    ../data/raw/Gourmet_Foods
[INFO]    [4]    ../data/raw/Industrial
[INFO]    [5]    ../data/raw/Jewelry
[INFO]    [6]    ../data/raw/Musical_Instruments
[INFO]    [7]    ../data/raw/Office_Products
[INFO]    [8]    ../data/raw/Software
[INFO]    [9]    ../data/raw/Watches
[INFO]    [10]    ../data/raw/Clothing
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
python3-pip is already the newest version (22.0.2+dfsg-1ubuntu0.4).
0 upgraded, 0 newly installed, 0 to remove and 14 not upgraded.
Requirement already satisfied: simplejson==3.19.2 in /usr/local/lib/python3.10/dist-packages (from -r ../data/requirements.txt (line 1)) (3.19.2)
WARNING: Running pip as the 'root' user can result in broken permissions and conflicting behaviour with the system package manager. It is recommended to use a virtual environment instead: https://pip.pypa.io/warnings/venv
[INFO]    Done setting pip3 up
[INFO]    Conversion ../data/raw/Arts done!
[INFO]    Conversion ../data/raw/Automotive done!
[INFO]    Conversion ../data/raw/Cell_Phones done!
[INFO]    Conversion ../data/raw/Gourmet_Foods done!
[INFO]    Conversion ../data/raw/Industrial done!
[INFO]    Conversion ../data/raw/Jewelry done!
[INFO]    Conversion ../data/raw/Musical_Instruments done!
[INFO]    Conversion ../data/raw/Office_Products done!
[INFO]    Conversion ../data/raw/Software done!
[INFO]    Conversion ../data/raw/Watches done!
[INFO]    Conversion ../data/raw/Clothing done!
[INFO]     JSON FileType
[INFO]    [0]    Arts.json
[INFO]    [1]    Automotive.json
[INFO]    [2]    Cell_Phones.json
[INFO]    [3]    Gourmet_Foods.json
[INFO]    [4]    Industrial.json
[INFO]    [5]    Jewelry.json
[INFO]    [6]    Musical_Instruments.json
[INFO]    [7]    Office_Products.json
[INFO]    [8]    Software.json
[INFO]    [9]    Watches.json
[INFO]    [10]    Clothing.json
 Done with sending Arts.json into the buffer and closing it
 Done with sending Automotive.json into the buffer and closing it
 Done with sending Cell_Phones.json into the buffer and closing it
 Done with sending Gourmet_Foods.json into the buffer and closing it
 Done with sending Industrial.json into the buffer and closing it
 Done with sending Jewelry.json into the buffer and closing it
 Done with sending Musical_Instruments.json into the buffer and closing it
 Done with sending Office_Products.json into the buffer and closing it
 Done with sending Software.json into the buffer and closing it
 Done with sending Watches.json into the buffer and closing it
 Done with sending Clothing.json into the buffer and closing it
 Started sending them into the combined.json
[INFO]     JSON FileType
[INFO]    [0]    combined.json
combined.json about to be json parsed
combined.json parsed
 Saving to text.txt
 Saved text.txt
 Saving to score.txt
 Saved score.txt
[INFO]     TXT FileType
[INFO]    [0]    score.txt
[INFO]    [1]    text.txt
[INFO]     TXT FileType
[INFO]    [0]    score.txt
[INFO]    [1]    noStopWord.txt
[INFO] noStopWord.txt changed to cleaned.txt
[INFO]     TXT FileType
[INFO]    [0]    score.txt
[INFO]    [1]    cleaned.txt
Categorization completed.
[INFO]     TXT FileType
[INFO]    [0]    hightext.txt
[INFO]    [1]    lowtext.txt
 Min is - 257576
Equalization completed.
[INFO]     TXT FileType
[INFO]    [0]    equalhightext.txt
[INFO]    [1]    equallowtext.txt
Files combined successfully.
[INFO] Combined - equalhightext_combined.txt
[INFO]     TXT FileType
[INFO]    [0]    equalhightext_combined.txt
```

mis

```cpp
std::vector<std::string> newlist = {"books_small_10000.json"};
Preprocessor review = Preprocessor(FileType::JSON,newlist);
review.Combine();
review.ConvertJsonToTxt();
review.dividePostiveandNegative(3);
// review.removeStopWords();
// review.removech();
review.saveEqualdivided();
review.Combine();
```

## NOTES

- After using `data/parser.py` some Json line field may be null
- Currently only Random Forest is showing promising results but issue is its promising results are with huge memory, might reduce the dataset size

## Dependencies, Sources and References

### [Json.hpp](./include/json.hpp)

- [nlohmann Json](https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp)
- [nlohmann Json Documentation](https://json.nlohmann.me/api/basic_json/)

## Ref

- Dataset source “SNAP: Web data: Amazon reviews,” Stanford.edu, 2024. https://snap.stanford.edu/data/web-Amazon-links.html (accessed Jan. 24, 2024).
