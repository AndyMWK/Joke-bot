
//these includes are done by my instructor. 
//#include "cmpt_error.h"    // These are the only permitted includes!                //cmpt_error.h was a headerfile that my instructor told students to use. 
#include "Chatbot.h"       //
#include <iostream>        // Don't include anything else.
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <ctime> 
#include <cassert>

using namespace std;

class Turing_bot : public Chatbot {
 string n;
 string firstGreeting;
 int turns = 0;
 //a struct that defines a knock knock joke
 struct joke {
   string noun;
   string theJoke;
 };
 vector <joke> jokes;
 vector <joke> jokeTold;
 vector <joke> jokesGiven;
 void setJokes() {
   joke j1;
   j1.noun = "broccoli";
   j1.theJoke = "broccoli doesn't have a last name silly";
   jokes.push_back(j1);
   joke j2;
   j2.noun = "tennis";
   j2.theJoke = "tennis is five times two";
   jokes.push_back(j2);
   joke j3;
   j3.noun = "spell";
   j3.theJoke = "okay, w-h-o";
   jokes.push_back(j3);
 }
 //checks for greetings that are peculiar
 bool checkForWeirdGreetings(string s) {
   for (int i=0;i<s.size();i++) {
     s.at(i)=tolower(s.at(i));
   }
   bool weirdGreeting = true;
     if (s.size() == 1) {
       //weird greeting if there is only one letter
       return weirdGreeting;
     }
     else if (s.at(0) < 'z' || s.at(0) > 'a') {
       //weird greeting if there are only a series of same symbols
       for (int i=0; i<s.size();i++) {
         if (s.at(i) != s.at(0)) {
           weirdGreeting = false;
         }
       }
     }
     else if (s.at(0) > 'z' || s.at(0) < 'a') {
       for (int i=0; i<s.size(); i++) {
         if(s.at(0) < 'z' || s.at(0) > 'a') {
           weirdGreeting = false;
         }
       }
     }
  return weirdGreeting;
 }
 bool findWord (string s, string q) {
   //first converts all letters to lower case
   for (int i=0;i<s.size();i++) {
     s.at(i)=tolower(s.at(i));
   }
   int pos=s.find(q);
   int sizeOfQ = q.size();
   if (s.size()< q.size()) {
     //return false as the size is less than the word looking for 
     return false;
   }
   if (pos>=0 && pos<s.size()) {
     if (pos>0 && (pos+sizeOfQ)<s.size()) {
       //checks for the case when the word is in the middle of a sentence
         if (s.at(pos-1)>'z' || s.at(pos-1)<'a') {
             if (s.at(pos+sizeOfQ)>'z' || s.at(pos+sizeOfQ)<'a') {
                 return true;
             }
             }
         }
     else {
     if (pos==0) {
       //checks for the case when the word is at the beginning
         if (s.size()==sizeOfQ) {
             return true;
         }
         else {
             if (s.at(pos+sizeOfQ)>'z' || s.at(pos+sizeOfQ)<'a') {
                 return true;
                 }
             }
         }
     if ((pos+sizeOfQ)==s.size()) {
       //checks for the case when the word is at the end of the sentence
         if (s.at(pos-1)>'z' || s.at(pos-1)<'a') {
             return true;
             }
         }
     }
 }
 return false;
}
  //a more generalized search for words that a lot of people don't always spell correctly
  bool findWordGeneralSearch (string s, string q) {
  
  for (int i=0;i<s.size();i++) {
    s.at(i)=tolower(s.at(i));
  }
  int sizeOfQ = q.size();
  int charThreshHold = 3;
  //this is the amount of letters that the word given can go over by as some people can make mistakes with some words
  if (s.size()< sizeOfQ) {
     return false;
  }
  else if ((s.size() + charThreshHold) <= sizeOfQ) {
   for (int i=0; i < sizeOfQ; i++) {
     if (s.at(i) != q.at(i)) {
       return false;
      }
    }
  }
  return true;
  }
  bool sameJoke (joke J, vector <joke> v) {
    //checks if the joke has alrady been told by user or alan
  for (joke I : v) {
  if (I.noun == J.noun) {
    if (I.theJoke == J.theJoke) {
       return true;
    }
    else {
     return false;
    }
  }
  }
  return false;
  }
  public:
  //pre-made inputs that will be used
  const string defaultFirstMessage = ". I tell knock-knock jokes!";

  const string greetings = "Hello! My name is ";

  const string weirdGreetingResponse = "Wow that's a weird way to say hi. ";

  const string startOff = "Ok! Let me start. Knock knock";

  const string knockKnock = "knock knock";

  const string responseToNoKnock = "Come on! Let me tell you a joke! ";

  const string responseToUser = "who's there?";

  const string listeningModePrompt = ".\nIf you have a joke, say knock knock before I say it!";

  const string whoQuestion = " who?";

  const string badJoke = "Wow. I never knew it was possible to be negatively funny. Ok, let me tell you a joke!";

  const string goodJoke = "That was pretty good! I want another one!";

  const string afterGoodJokeNoKnock = "tell me a knock knock joke!";

  const string tellMeNew = "tell me a new joke!";
//this bot keeps track of what was said and outputs an answer based upon previous output

string previousMessage;

  Turing_bot(string s) : n(s) {
  string firstMessage = greetings + s + defaultFirstMessage;
  firstGreeting = firstMessage;
  setJokes();
  vector <joke> jokesGiven;
  }
  string name() const {
    return n;
  }
  //all bool variables that decides what alan will say

  bool responseToWeirdGreeting=false;

  bool wantsToKnock = false;

  bool listeningMode = false;

  bool jokeOver = false;

  bool noMoreJoke = false;

  joke theJoke;

  string jokeNoun;

  string jokeJoke;

  void tell (const string &s) {
  //checks if user typed knock knock. If typed, it will decide what alan will say later
  bool findKnock = findWord(s, knockKnock);
  
    if (turns == 0) {
    if (s.size() != 0) {
      //checks for odd greetings
     responseToWeirdGreeting = checkForWeirdGreetings(s);
    }
    }
  else if (jokeOver && findKnock) {
    //if Alan has already told a joke and user typed knock knock, alan will listen to the user's jokes
     previousMessage = responseToUser;
     listeningMode = true;
  }
  else if (!listeningMode) {
    //this is when alan is telling a joke.
   if (previousMessage == startOff || previousMessage == knockKnock) {
     //checks if the user typed who or there when alan said knock knock
     bool who = findWordGeneralSearch(s, "who");
     bool there = findWord (s, "there");
     if (who && there) {
       wantsToKnock = true;
     }
   }
   else if (previousMessage == theJoke.noun) {
     //checks if the user responded correctly to alan's jokes
     bool prevWord = findWord (s, theJoke.noun);
     bool who = findWordGeneralSearch(s, "who");
      if (who && prevWord) {
       wantsToKnock = true;
     }
   }
 }
  else if(listeningMode) {
    //this is when alan is listening to a joke
   if (previousMessage == goodJoke || previousMessage == afterGoodJokeNoKnock) {
     //this is when alan asked the user to give him a joke and alan checks the user's response
     if (findKnock) {
       previousMessage = responseToUser;
     }
     else if (!findKnock) {
       previousMessage = afterGoodJokeNoKnock;
     }
   }
   else if (previousMessage == responseToUser) {
     //creates a response based on the user's joke
     jokeNoun = s;
     previousMessage = s + whoQuestion;
   }
   else if (previousMessage == (jokeNoun + whoQuestion)) {
     //alan's reactions to jokes
     joke jokeTold;
     jokeTold.noun = jokeNoun;
     jokeTold.theJoke = s;
     //if joke has alrady been told, alan will respond that it has been told and he wants a new one
     bool sameJ = sameJoke(jokeTold, jokesGiven);
     jokesGiven.push_back(jokeTold);
     if (sameJ) {
       previousMessage = tellMeNew;
     }
     //if not told, randomly decides if alan likes the joke or not
     else if(!sameJ) {
       int goodOrBad = rand()% 2 + 1;
       if (goodOrBad == 2) {
         previousMessage = badJoke;
       }
       if (goodOrBad == 1) {
         previousMessage = goodJoke;
       }
     }
   }
 }
}

  string get_reply() {
    //this if staement branch is for when alan is greeting
  if (turns == 0) {
    if (responseToWeirdGreeting) {
      //if the greeting from user is considered odd, alan gives a different response
      turns++;
      return weirdGreetingResponse + firstGreeting;
    }
    else {
      turns++;
      return firstGreeting;
    }
  }
  if (!listeningMode) {
    jokeOver = false;
    //joke has begun and joke is not over so its false
    if (turns == 1) {
      turns++;
      previousMessage = startOff;
      return startOff;
    }
    if (previousMessage == startOff || previousMessage == knockKnock) {
      //alan picks a random joke from his collection of jokes
      int randomNum = rand() % jokes.size();
      if (wantsToKnock) {
        theJoke = jokes.at(randomNum);
        previousMessage = theJoke.noun;
        wantsToKnock = false;
        //also checks if the joke has been told before. If so, he will tell a seperate response
        bool isSameJoke = sameJoke(theJoke, jokeTold);
        if (!isSameJoke) {
          jokeTold.push_back(theJoke);
          return previousMessage;
        }
        else if (isSameJoke) {
          return "I have told you this before..." + previousMessage;
        }
      }
      else if (!wantsToKnock) {
        //if the user doesn't want to hear alan's jokes, this is alan's response
        return responseToNoKnock + knockKnock;
      }
    }
    if (previousMessage == theJoke.noun) {
      if (wantsToKnock) {
        //this is when alan's jokes are over and alan has told his joke
        previousMessage = theJoke.theJoke;
        wantsToKnock = false;
        jokeOver = true;
        if (turns == 2) {
          turns++;
          return theJoke.theJoke + listeningModePrompt;
        }
        else {
          return theJoke.theJoke;
        }
      }
      else if (!wantsToKnock) {
        return responseToNoKnock;
      }
    }
    if (previousMessage == theJoke.theJoke) {
      //after joke is over, he will occasionally ask the user for jokes. Approx. 1 in 5 chance
      int askForJoke = rand()%5 + 1;
      if (askForJoke == 5 && !noMoreJoke) {
        previousMessage = afterGoodJokeNoKnock;
        listeningMode = true;
        return "Hey why don't you " + previousMessage;
      }
      noMoreJoke = false;
      previousMessage = knockKnock;
      return knockKnock;
    }
  }
  else if (listeningMode) {
    //alan is now listening
    jokeOver = false;
    if (previousMessage == afterGoodJokeNoKnock) {
      //if he decides the joke is good, he will ask for more jokes
      previousMessage = goodJoke;
      return afterGoodJokeNoKnock;
    }
    if (previousMessage == responseToUser) {
      //basic user starter prompt for them to tell a joke
      return previousMessage;
    }
    if (previousMessage == (jokeNoun + whoQuestion)) {
      //basic response to user's joke
      return previousMessage;
    }
    if (previousMessage == goodJoke || previousMessage == badJoke) {
      if (previousMessage == badJoke) {
       //if joke was bad, user cannot give jokes and alan gives jokes
       noMoreJoke = true;
       listeningMode = false;
       int randomNum = rand() % jokes.size();
       theJoke = jokes.at(randomNum);
       previousMessage = theJoke.theJoke;
       return badJoke;
     }
     if (previousMessage == goodJoke) {
       //if joke was good, this allows the user to keep giving jokes
       jokeOver = true;
       return previousMessage;
     }
   }  
   if (previousMessage == tellMeNew) {
     //if joke was already told, alan asks for a new joke
     jokeOver = true;
     previousMessage = afterGoodJokeNoKnock;
     return tellMeNew;
    }
  }
  return previousMessage;
  }
};

//this was done by my instructor. 
void converse(Chatbot* a, Chatbot* b, int max_turns) {
 for(int turn = 1; turn <= max_turns; turn++) {
   string a_msg = a->get_reply();
   //cout << "(" << turn << ") " << a->name() << ": " << a_msg << "\n";
   turn++;
   if (turn > max_turns) return;
   b->tell(a_msg);
   string b_msg = b->get_reply();
   //cout << "(" << turn << ") " << b->name() << ": " << b_msg << "\n";
   a->tell(b_msg);
 }
}

int main() {
  srand(time(nullptr));
  User_bot user("user");
  //Mirror_bot mbot("repeto", "sup");
  //Random_bot rbot("Rando", {"yo", "sup", "jeez"});
  //Random_bot rbot("Rando", "word.txt");
  //Datetime_bot rbot("time", {"sup", "bro", "hello"});
  Turing_bot rbot("alan");
  converse(&user, &rbot, 30);
}
