# cpp-t9
A T9 typing system written in C++17

cpp-t9 is a basic T9 typing system implementation that allows you to learn a statistical model from training data to generate suggestions based on entered T9 keys.

## Usage

There are two examples provided inside [main.cpp](src/main.cpp).
Both examples train a statistical model from a collection of Tweets from Donald Trump. This training data is placed in the [data/](data/) folder and can be exchanged as needed. Note that characters that are not part of the *Corpus symbols* are stripped away.

### Symbol definitions

* T9 keys: "0123456789*#"
* Corpus symbols: "a-zA-Z0-9 .,"

The corpus symbols are assigned to the keys as follows:

| T9 Key | Corpus Symbols    |
|--------|-------------------|
| #      | " " (space)       |
| *      | "" (not assigned) |
| 0      | "0"               |
| 1      | ".,1"             |
| 2      | "aAbBcC2"         |
| 3      | "dDeEfF3"         |
| 4      | "gGhHiI4"         |
| 5      | "jJkKlL5"         |
| 6      | "mMnNoO6"         |
| 7      | "pPqQrRsS7"       |
| 8      | "tTuUvV8"         |
| 9      | "wWxXyYzZ9"       |

### Completion example

This example shows how a given sequence of T9 keys is used generate a text suggestion based on a learned statistical model.

Here the key sequence `366253#87867` is entered:

```
========================================================
Key to Corpus Table:
========================================================
#: " "
*: ""
0: "0"
1: ".,1"
2: "aAbBcC2"
3: "dDeEfF3"
4: "gGhHiI4"
5: "jJkKlL5"
6: "mMnNoO6"
7: "pPqQrRsS7"
8: "tTuUvV8"
9: "wWxXyYzZ9"
========================================================

Loaded train data (3091794 bytes)
Train data validated successfully
Loaded test data (140 bytes)
Test data validated successfully
Loading the corpus took: 168.95 ms
Building the model took: 856.33 ms

Typing sequence: 366253#87867
Autocomplete suggestions:
    (9.6757): "Donald Trump"
    (12.8488): "DONALD TRUMP"
    (13.6142): "donald Trump"
    (15.2169): "DONALD Trump"
    (15.7823): "Donald TRUMP"
    (15.8735): "Donald trump"
    (16.9666): "eonald Trump"
    (17.7397): "Donald Trums"
    (18.9669): "DONALD TRUMp"
    (21.4127): "Donald Truns"
    (21.6783): "donald Trums"
    (21.9004): "Donald TRUMp"
    (22.4398): "Donald truns"
    (23.2810): "DONALD Trums"
    (23.9376): "Donald trums"
Autocomplete took: 8246.55 ms
Done!
```

### Evaluation example

This example shows how the statistical model learned from a training corpus can be evaluated. For a given T9 symbol sequence the system generates a text suggestion. This suggested text is compared to the known ground truth the T9 key sequence originated from.

Here the evaluation of a model with a ngram length of four and an evaluation text length of 140 characters. For meaningful results longer test sequences should be used:

```
========================================================
Key to Corpus Table:
========================================================
#: " "
*: ""
0: "0"
1: ".,1"
2: "aAbBcC2"
3: "dDeEfF3"
4: "gGhHiI4"
5: "jJkKlL5"
6: "mMnNoO6"
7: "pPqQrRsS7"
8: "tTuUvV8"
9: "wWxXyYzZ9"
========================================================

Loaded train data (3091794 bytes)
Train data validated successfully
Loaded test data (140 bytes)
Test data validated successfully
Loading the corpus took: 168.96 ms
Building the model took: 848.68 ms
Evaluation: duration: 8835.71 ms,  error: 0.064
Done!
```

### Parameters

There are two main parameters that control the model creation process:

* **ngram_length**: The Ngram length to use for building the statistical  model.
* **n_paths**: After every T9 key entered, the system generates a suggestion and prunes the internal tree structure. ```n_paths``` defines how many of the best paths (different suggestions) should survive the pruning. Therefore, in the end there exist up to this number of text suggestions for an entered key sequence.



## Build

### Debug

```
mkdir -p build/debug
cd build/debug
cmake -DCMAKE_BUILD_TYPE=Debug ../
make
```

### Release

```
mkdir -p build/release
cd build/release
cmake -DCMAKE_BUILD_TYPE=Release ../
make
