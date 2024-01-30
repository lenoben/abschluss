# ModelFlow

This directory houses the codebase for preprocessing, model building, training and evaluation.

## FileFormat during preprocessing
There are 2 major file format, `FileType::TXTGZ` is there if we do not whant to use the python script to parse it into Json

- .txt
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

- .json (multi-object seperated by newlines)
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

## NOTES
- After using `data/txt_gz_parser.py` some Json line field may be null

## Dependencies, Sources and References

- [nlohmann Json](https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp)
- [nlohmann Json Documentation](https://json.nlohmann.me/api/basic_json/)

## Ref
- Dataset source “SNAP: Web data: Amazon reviews,” Stanford.edu, 2024. https://snap.stanford.edu/data/web-Amazon-links.html (accessed Jan. 24, 2024).
‌