// Matthew Rutigliano
// P3: Card Game
// Purpose: Impliment the Stack and Queue classes to run a fictitious card game.
// Inputs: Player names
// Process: A stack of 52 cards (4 sets of 1-13) is created and shuffled. Two player structs are initialized
//          and given the inputted names. Each player has a queue representing their hand of cards, into which
//          seven cards are dealt in an alternating fashion. Each player then takes turns putting cards into
//          the discard stack. If their card is bigger than the last one put in, their turn is over.
//          if the two cards equal, the player's hand has one card added to it. If the player's card
//          is smaller, two cards are added. If the deal stack runs out, the discard stack is
//          pushed into it in a reverse fashion. The game ends when one player runs out of cards.
//          At this point the players are asked if they'd like to play again, with all the stacks and queues
//          being emptied and the deck being reshuffled if they say yes.
// Outputs: Player's hands, top of the discard stack

#include "stack.h"
#include "queue.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Player struct holding their cards, how many cards they have and their name
struct Player
{
  Queue hand;
  int numCards = 0;
  string playerName;
};

void draw(Player&, int);
// Queues drawn card in player's hand
// Precondition: Player has been initialized, card has been popped from stack
// Postcondition: Card is now in player's hand and their number of cards has incrimented

int play(Player&);
// Plays card in player's hand
// Precondition: Player has cards to play
// Postcondition: The first card in their hand has been dequeued, and their number of cards
//                decremented.

void printHand(Player&);
// Prints player's hand
// Precondition: Player has been initialized
// Postcondition: None

void takeTurn(Player&, Stack&, Stack&);
// Plays out player's turn
// Precondition: Player, deal and discard stacks have been initialized
// Postcondition: Player has drawn appropriate amount of cards. Their card has been discarded,
//                and the discard has been turned over if the deal stack is empty.

void win(Player&, bool&);
// Sees if player has won
// Precondition: Player has been initialied
// Postcondition: Bool is set to true if player's hand is empty

void resetDeck(Stack&);
// Resets deck
// Precondition: Deck stack has been initialized
// Postcondition: Deck has been emptied

void resetPlayer(Player&);
// Resets player's hand
// Precondition: Player has been initialized
// Postcondition: Player's hand is now empty

void shuffle(Stack&, int[], const int);
// Creates and shuffles deck
// Precondition: Deck stack, temporary array and size have been initialized
// Postcondition: Deck stack now has 52 randomly organized cards of value 1-13

int main()
{

  // Size of card deck
  const int DECK_SIZE = 52;

  // Deal and discard stacks
  Stack deal(DECK_SIZE);
  Stack discard(DECK_SIZE);

  // Array for shuffling cards
  int pile[DECK_SIZE];

  // Players 1 and 2
  Player p1;
  Player p2;

  // Boolean for determing whose turn it is
  bool p1Turn = true;

  // Boolean for determining if the game is won
  bool isWon = false;

  // Boolean and character for seeing if the game is repeating
  bool repeat = false;
  char ans;

  int val;

  cout << "From the maker of TicTacToeX: Game of the Year Edition comes 'Card game' the new sensation!" << endl
       << "You and one other lucky player are dealt 7 cards. Each turn consists of a player comparing their " << endl
       << "card to the top of the discard. If it's more, you put it down. If it equals you put it down and " << endl
       << "draw one card, and if it's less you draw two. This dazzling computer simulation puts helplessness " << endl
       << "on the forefront, creating an experience my roommate calls 'Eerily realistic.'" << endl;
  cout << "Would you like to play cards? y/n ";
  cin >> ans;
  if (toupper(ans) == 'Y')
    repeat = true;

  cin.ignore();

  // Inputting player names
  if (repeat)
    {
      cout << "Player 1's name:" << endl;
      getline(cin, p1.playerName);

      cout << "Player 2's name:" << endl;
      getline(cin, p2.playerName);
    }
  
  while (repeat)
    {
      
      // Shuffling deck
      shuffle(deal,pile,DECK_SIZE);
      // Dealing cards
      for (int i = 0; i < 7; i++)
        {
          deal.pop(val);
          draw(p1,val);
          deal.pop(val);
          draw(p2,val);
        }

      // Put first card on discard
      deal.pop(val);
      discard.push(val);

      while (!isWon)
        {
          // Prints hands
          cout << "Cards in hand:" << endl << "--------------" << endl << endl;
          printHand(p1);
          printHand(p2);

          // P1's turn
          if (p1Turn)
            {
              // Takes turn
              takeTurn(p1, discard, deal);

              // Sets boolean for P2's turn
              p1Turn = false;

              // Check if P1 won
              win(p1,isWon);
            }
          // P2's turn
          else
            {
              // Takes turn
              takeTurn(p2, discard, deal);

              // Sets boolean for P1's turn
              p1Turn = true;

              // Checks if P2 won
              win(p2,isWon);
            }
        }
      cout << "Would you like to play again? y/n ";
      cin >> ans;
      if (toupper(ans) == 'N')
        {
          repeat = false;
          cout << "Thanks for playing the newest computer experience taking Seattle U by storm!" << endl;
        }
      // Reset game
      else
        {
          isWon = false;
          resetDeck(deal);
          resetDeck(discard);
          resetPlayer(p1);
          resetPlayer(p2);
        }
    }
  
  return 0;
}

void draw(Player & p, int card)
{
  p.hand.enqueue(card);
  p.numCards++;
}

int play(Player & p)
{
  int card;
  p.hand.dequeue(card);
  p.numCards--;
  return card;
}

void printHand(Player & p)
{
  int card;
  cout << p.playerName << "'s cards:" << endl;
  for (int i = 0; i < p.numCards; i++)
    {
      p.hand.dequeue(card);
      cout << card << " ";
      p.hand.enqueue(card);
    }
  cout << endl << endl;
}

void takeTurn(Player & p, Stack & trash, Stack & fresh)
{
  cout << p.playerName << ", press RETURN to take a turn." << endl;
  cin.get();
  int top = trash.peek();
  int transfer = 0;
  int move = play(p);

  // Transfer is any card being drawn by the player
  // Move is the card that the player discards that turn

  // Turning deck over
  if (fresh.isEmpty())
    {
      trash.pop(top);
      while (!trash.isEmpty())
        {
          trash.pop(transfer);
          fresh.push(transfer);
        }
      trash.push(top);
    }
    
  cout << "Top of the stack is " << top << "." << endl << endl;

  if (move > top)
    {
      cout << "Your card " << move << " is larger than " << top << "." << endl;
      cout << "Nice!" << endl << endl;
    }
  else if (move == top)
    {
      cout << "Your card " << move << " is equal to " << top << "." << endl;
      cout << "You draw one card." << endl << endl;
      fresh.pop(transfer);
      draw(p,transfer);
    }
  else
    {
      cout << "Your card " << move << " is less than " << top << "." << endl;
      cout << "You draw two cards." << endl << endl;
      fresh.pop(transfer);
      draw(p,transfer);
      fresh.pop(transfer);
      draw(p,transfer);
    }
  trash.push(move);
}

void win(Player & p, bool & win)
{
  if (p.hand.isEmpty() == true)
    {
      win = true;
      cout << p.playerName << " wins!" << endl;
    }
}

void resetDeck(Stack & deck)
{
  int temp;
  while (!deck.isEmpty())
    {
      deck.pop(temp);
    }
}

void resetPlayer(Player & p)
{
  while (!p.hand.isEmpty())
    {
      play(p);
    }
}

void shuffle(Stack & deck, int pile[], const int SIZE)
{
  int l = 0;
  int swap = 0;
  int spot = 0;
  for (int i = 0; i < 4; i++)
    {
      for (int j = 1; j < 14; j++)
        {
          pile[l] = j;
          l++;
        }
    }

  unsigned seed = time(0);
  srand(seed);

  // Array is looped through, with a random spot within the array being
  // chosen to swap values with
  for (int i = 0; i < SIZE; i++)
    {
      spot = (rand() % (SIZE-1));
      swap = pile[spot];
      pile[spot] = pile[i];
      pile[i] = swap;
    }
      
  for (int i = 0; i < SIZE; i++)
    {
      deck.push(pile[i]);
    }
}
  
