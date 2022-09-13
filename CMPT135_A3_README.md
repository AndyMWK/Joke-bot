# Assignment 3: Chatbots

In this assignment your task is to implement and test a number of different
chatbots.

## Getting Started

For this assignment, put all the code you write into [a3.cpp](a3.cpp). Note
that there is a helper function called `converse` that you can, if you like,
use to help develop and test your chatbots. **You can change `converse` if you
like**. One way to test a new chatbot is to run it with a `User_bot` (see
below) in this function.

Among other files, [a3.cpp](a3.cpp) includes [Chatbot.h](Chatbot.h), which has
the `Chatbot` base class your classes must inherit from. All the methods in
[Chatbot.h](Chatbot.h) are virtual and abstract, and so your inheriting
classes should implement all of them in a sensible way. We want to see you use
good programming style and make good use of C++'s object-oriented features.

Every chatbot class you write should accept a name (as a `string`) so that
chatbots can be given unique names. The `name()` method should return the name
of the chatbot.

**Important**: For each chatbot, make sure to implement the constructors
*exactly* as given in the examples and description.

Make sure to test all your chatbots!

Here's a class diagram for all the clases in this assignment:

![chatbot class diagram](chatbotClassDiagram.png)


## Chatbot 1: Mirrored Replies

Implement a chatbot class (that inherits from `Chatbot`) called `Mirror_bot`
that always replies with the last string that it was told. If it needs to
speak before being told anything, then its reply is a special "first reply"
string that is given to it in its constructor.

For example:

```cpp
Mirror_bot mbot("repeato", "repeato is ready to go!");
```

The name of `mbot` is `repeato`, and if it is asked to speak first, it
will say the second string passed to the constructor.


## Chatbot 2: Random Replies

Implement a chatbot class (that inherits from `Chatbot`) called `Random_bot`
that chooses a random reply from a list of given replies. It should have
constructors that allow lists of replies to be read in at least the two
following ways.

### A vector<string> of Replies

`Random_bot` should have a constructor that has a `vector<string>` as its
second parameter (the first parameter being the name of the chatbot). If the
passed-in vector is empty, call `cmpt::error` in the constructor with a
helpful message.

For example:

```cpp
Random_bot cat{"Mittens", {"meow", "purrr", "meeeeow"}};
```

Calling `cat.get_reply()` returns `"meow"`, `"purrr"`, or `"meeeeow"` at
random.

### Replies from a Text File

`Random_bot` should have a constructor that has a `string`, for the name of a
file, as its second parameter (the first parameter being the name of the
chatbot). Each non-empty line of the file contains one reply. If the file
can't be opened, or if it is empty, then call `cmpt::error` in the constructor
with a helpful message.

For example, suppose the text file `dog_sounds.txt` contains this:

```
woof
ruff
yap yap yap
bow wow  
```

Then we can construct another random reply bot like this:

```cpp
Random_bot dog{"Fido", "dog_sounds.txt"};
```

Calling `dog.get_reply()` returns `"woof"`, `"ruff"`, `yap yap yap`, or `"bow
wow"` at random.


## Chatbot 3: The User

Implement a chatbot class (that inherits from `Chatbot`) called `User_bot`
that asks the user to enter a line of text (on `cin`) whenever `get_reply` is
called. `tell` should print the message to the screen. This lets the user talk
with other chatbots using a function like `converse` in [a3.cpp](a3.cpp).

For example:

```cpp
User_bot user{"stan"};
```

## Chatbot 4: Current Time and Date

Implement a chatbot class (that inherits from `Chatbot`) called `Datetime_bot`
that replies with the current date and time just when the last string told to
it contains either "date" or "time" (or both) as a substring. If neither
"date" nor "time" appears, then the reply is a default message chosen at
random from a `vector<string>` of messages supplied in the constructor.

When checking for "date" or "time", the case should **not matter**, e.g. if
the last string told to the bot was "what's the dAtE???", then that counts as
containing "date".

For example:

```cpp
Datetime_bot dt_bot{"deetee", {"Ask me about the date or time!", 
                               "I know the date and time!"}};
```

Here, the first input is the bot's name, and the second is the
`vector<string>` of messages that will be chosen from at random when neither
"date" nor "time" was in the last string it was told.

If both "date" and "time" appear in the input, then your chatbor should print
both the date and time.


## Chatbot 5: Turing Bot

`The Turing Test <https://en.wikipedia.org/wiki/Turing_test>`_ is a famous
thought experiment that some computer scientists believe can be used to
determine if a program has human-level intelligence. The program that we are
testing for intelligence and a person (who we assume is intelligent) have a
text-only conversation using a chatbot-like interface. If the program can
fool the human into thinking it's a real person, then, some say, the program
must have human-level intelligence.

Implement an **original** and interesting chatbot class called `Turing_bot`
that tries to pass the Turing test. Make it is as smart and feature-rich as
you can. To simplify things a bit, it's okay if your chatbot is restricted to
one particular topic, as long as it is interesting and tries to be intelligent
in some way. You can expand upon ideas from the previous bots, or try
something new.

Please make something original and interesting, something that you would be
proud to show off to others. **Do a little bit of research on the web to get
ideas for other kinds of chatbots**.

In the comments for this chatbot, please include some description of the
techniques your chatbot uses, and provide links for any research you did or
help you received.

Your `Turing_bot` should be constructed like this:

```cpp
Turing_bot smart_bot("Alan");
```


## Submit Your Work

Please put all your code into [a3.cpp](a3.cpp), and submit it on Canvas.
Implement **all** the methods and functions exactly as described, otherwise
the marking software will probably give you 0!

The only file you submit is [a3.cpp](a3.cpp): *don't* submit any other files.
The marker will use the standard [makefile](makefile) to compile it, and a
copy of [cmpt_error.h](cmpt_error.h) and `Chatbot.h` will be in the same
folder as [a3.cpp](a3.cpp) when it's tested.

## Basic Requirements

Before we give your program any marks, it must meet the following basic
requirements:

- It must compile on Ubuntu Linux using the standard course
  [makefile](makefile):
  
  ```
  $ make a3
  g++  -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   a3.cpp   -o a3
  ```
  
  If your program fails to compile, your mark for this assignment will be 0.

  A copy of [cmpt_error.h](cmpt_error.h) will be in the same folder as
  [a3.cpp](a3.cpp) when it's compiled, so your program can use `cmpt::error`
  if necessary.

- It must have no memory leaks or memory errors, according to `valgrind`,
  e.g.:

  ```
  $ valgrind ./a3
    
  // ... lots of output ... 
  ```

  A program is considered to have no memory error if:

  - In the `LEAK SUMMARY`, `definitely lost`, `indirectly lost`, and `possibly
    lost` must all be 0.

  - The `ERROR SUMMARY` reports 0 errors.

  - It is usually okay if **still reachable** reports a non- zero number of
    bytes.

- **You must include the large comment section with student info and the
  statement of originality**. If your submitted file does not have this, then
  we will assume your work is not original and it will not be marked.
  
If your program meets all these basic requirements, then it will graded using
the marking scheme on Canvas.

## Marking Scheme

### Source Code Readability (6 marks)

- All names of variables, functions, structs, classes, etc. are sensible,
  self-descriptive, and consistent.

- Indentation and spacing is perfectly consistent and matches the structure of
  the program. All blank lines and indents should have a reason.

- All lines are 100 characters in length, or less.

- Comments are used when appropriate, e.g to describe code that is tricky or
  very important. There are no unnecessary comments, and no commented-out
  code.

- Appropriate features of C++ are used in an appropriate way. For example, do
  **not** use a feature of C (like C-style strings) when there is a better C++
  feature (e.g. the standard `string` class). Don't use any features you don't
  understand.

- Overall, the source code is easy to read and understand.

### Chatbots 1 to 4 (8 marks)

**2 marks** for each complete and correct chatbot that works as intended.

As mentioned above, make sure that each chatbot has a *exactly* the
constructor given in the description/example. Each missing pr incorrect
constructor will result in a penalty of at least -0.5 marks.


### Chatbot 5 (5 marks)

**4 marks** for an interesting and original chatbot. This chatbot should have
as many features as possible (e.g. at the very least as many features as
chatbot 2 and 4 combined). Obviously low-effort chatbots will not get full
marks.

**1 mark** for describing techniques the chatbot uses, and links to research.
