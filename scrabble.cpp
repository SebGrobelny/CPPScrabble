//Authors: Sebastian Grobelny Nicki Padar
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

class Word
{
public:
	string real_word;
	int word_value;
	Word();
	Word(string rhs, int data);
	bool operator< (const Word &rhs)const;
	bool operator== (const Word &rhs) const;
};

typedef map<char, short> Word_Value;

void makeSet(set<string> &words, Word legal_word, set<Word> &word, Word_Value word_value);
void findValue( Word &temp, Word_Value word_value );
void findScrabble(string File, set<Word> &output, set<Word> &word,Word_Value word_value, int &truth);
void printTopFour(set<Word> output, string File, int &truth);

Word::Word() {}

Word::Word(string rhs, int dat) : real_word(rhs), word_value(dat)
{
}

bool Word::operator< (const Word &rhs)const
{
	return((real_word < rhs.real_word));
}

bool Word::operator== (const Word &rhs) const
{
	return( (real_word == rhs.real_word));
}

void makeSet(set<string> &words, Word legal_word, set<Word> &word, Word_Value word_value)
{
	for (set<string>::iterator dad_itr = words.begin(); dad_itr != words.end(); dad_itr++)
	{
		int position = 0;
		legal_word.word_value = 0;
		map<char, short>::iterator itr = word_value.begin();

		while(itr != word_value.end())
		{
			string temp(1, itr->first);
			if (dad_itr->find(temp.c_str(),position,1) != string::npos)
			{
				//cout<< " word " << *dad_itr <<endl;
				legal_word.word_value = legal_word.word_value + itr->second;
				position = dad_itr->find(temp.c_str(),position,1) + 1;

			}

			else
			{
				//cout << " word " << *dad_itr << endl;
				itr++;
				position = 0;

			}
		}

		legal_word.real_word = *dad_itr;
		
		word.insert(legal_word);


	}

}

void findValue( Word &temp, Word_Value word_value )
{
	map<char, short>::iterator j = word_value.begin();
	int position = 0;

	while( j != word_value.end())
	{
	
		if (temp.real_word.find(&j->first, position, 1) != string::npos)
		{
			temp.word_value = temp.word_value + j->second;
			position = temp.real_word.find(&j->first, position, 1) + 1;
			//cout << j->first << "position" << position << endl;
		}
		else
		{
			j++;
			position = 0;

		}
	}
  // cout << " word " << temp.real_word << " value : " << temp.word_value << endl;
}
void findScrabble(string File, set<Word> &output, set<Word> &word, Word_Value word_value, int &truth)
{
   //cout << "in here";
	//int biggest = 0;
	Word local_out;
	set<Word>::iterator it; 

        sort(File.begin(), File.end());	
			while(next_permutation(File.begin(),File.end()))
			{
				for(int ku = 0; ku < File.size(); ku++)
				{
					string myfinal = File.substr(ku);
					Word temp (myfinal, 0);
					
            		if(	word.find(temp) != word.end() )
					{
						//cout << "in hera ";

						set<Word> :: iterator itr1 = word.find(temp);
						temp.word_value = itr1->word_value;

						cout << "word: " << temp.real_word << " value: " << temp.word_value << endl;

						output.insert(temp);
						if( temp.word_value > truth)
						{
							truth = temp.word_value;
						}


						//break;


					}

					//cout << "im here" << endl;

				}
			}

     
}


void printTopFour(set<Word> output, string File, int &truth)
{
  int biggest = 0;
  set<string> final_ones;
  string strung;
  
   
//set<Word>:: iterator itr1 = output.begin()

  cout << setw(2) << right << truth << " " << File << ":";
     //final_ones.insert(itr2->real_word);
     //biggest = itr2->word_value;
     //strung = itr2->real_word;
     //cout << biggest << " " << strung << endl;
     //itr2++;
   for (set<Word>::iterator itr2 = output.begin(); itr2!=output.end(); itr2++)
   {
   	if (itr2->word_value == truth)
     final_ones.insert(itr2->real_word);
   }
   for(set<string>::iterator i = final_ones.begin(); i!=final_ones.end(); i++)
   {
     cout << " " << *i ;
   }
    cout << endl;
}

int main(int argc, const char **argv) 
{
	short value[26] = {1, 3, 3, 2, 1, 4, 2, 4, 2, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

	ifstream inf1("words.txt");
	ifstream inf2(argv[1]);
	set<string> words;
	set<Word> word;
	//set<string> input;
	Word legal_word;
	string text, File;
	Word_Value word_value;
	char alpha = 'a';
	//char up_alpha = 'A';
	
	set<Word> output;
	Word local_out;
	set<string> raw;
    int truth = 0, fruth = 1;

	for (int i = 0; i < 26; i++)
	{
		word_value.insert(Word_Value::value_type(alpha, value[i]));
		alpha++; //stores each letter with its value in a map
	} //for

	while(getline(inf1, text))
	{
		 fruth = 1;
		 for( char up_alpha = 'A'; up_alpha < 'a'; up_alpha++)
		{
			if (strncmp(text.c_str(), &up_alpha, 1) == 0 || text.size() > 7)
				{
				fruth = 0;
				break;
                }   


		} //insert words.txt content into a set
		if(fruth != 0)
		{
		    //cout << "inserting : "<< text << endl;
			words.insert(text);
			//fruth = 1;
			//up_alpha++;
	    }
	}
	
	makeSet(words, legal_word, word, word_value); //store the words with their values into set
	
	while(getline(inf2,File))
	{
	    findScrabble(File,output, word, word_value, truth);
	   if(truth != 0)
         printTopFour(output, File, truth);
       else
         cout << "0 "<< File << ": No words found."<< endl;
      truth = 0;
      set<Word> new_output;
      output = new_output;
    }

return 0;
}
