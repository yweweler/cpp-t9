# cpp-t9
A T9 typing system written in C++17

cpp-t9 is a basic T9 typing system implementation that allows you to learn a statistical model from training data to generate suggestions based on entered T9 keys.

## Usage

There are two examples provided inside [main.cpp](src/main.cpp).
Both examples train a statistical model from a collection of Tweets from Donald Trump. This training data is placed in the [data/](data/) folder and can be exchanged as needed. Note that characters that are not part of the *Corpus symbols* are stripped away.

### Symbol definitions

* Lexicon symbols (T9 keys): "0123456789*#"
* Corpus symbols: "a-zA-Z0-9 .,"

### Completion example

This example shows how a given sequence of T9 keys is used generate a text suggestion based on a learned statistical model.

Here the key sequence `366253#87867` is entered:

```
TODO
```

### Evaluation example

This example shows how the statistical model learned from a training corpus can be evaluated. For a given T9 symbol sequence the system generates a text suggestion. This suggested text is compared to the known ground truth the T9 key sequence originated from.

Here the evaluation of a model with a ngram length of four and an evaluation text length of 140 characters. For meaningful results longer test sequences should be used:

```
TODO
```

### Parameters

There are two main parameters that control the model creation process:

* **ngram_length**: The Ngram length to use for building the statistical  model.
* **number_paths**: After every T9 key entered, the system generates a sugegstion and prunes the internal tree structure. ```number_paths``` defines how many of the best paths (different suggestions) should survive the pruning. Therefore, in the end there exist up to this number of text suggestions for an entered key sequence.



## Build

### Debug

```
mkdir debug
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ../
make
```

### Release

```
mkdir release
cd release
cmake -DCMAKE_BUILD_TYPE=Release ../
make
