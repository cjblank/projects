#include <iostream>
using namespace std;

class NumberCount
{
      private:
            int min, max;
            int *array;

      public:



      NumberCount(int minimum, int maximum)
      {
            min = minimum;
            max = maximum;
            array = new int[max-min+1];

            for(int i = 0; i < (max-min+1); i++)
            {
                array[i] = 0;
            }
      }

      void addElement(int number)
      {
            if((number >= min) && (number <= max))
            {
                  array[number-min]++;
            }else
            {
                  cout << number << " Out of range;";
            }
      }

      void removeElement(int number)
      {
            if((number >= min) && (number <= max))
            {
                 if(array[number-min] != 0)
                      array[number-min]--;
                 else
                      cout << number << " not present;";
            }else
            {
                  cout << number << " Out of range;";
            }
      }

      void display()
      {
            cout << '\n';
            for(int i = 0; i < (max-min+1); i++)
            {
                  cout << min + i << ": " ;

                  for(int j = 0; j < array[i]; j++)
                  {
                      cout << "*";
                  }

                  cout << '\n';
            }
      }

      int getCount()
      {
            int sum = 0;

            for(int i = 0; i < (max-min+1); i++)
            {
                sum += array[i];
            }

            return sum;
      }
};


int main()
{
      NumberCount N(1,6);

      N.addElement(2);
      N.addElement(2);
      N.addElement(2);
      N.addElement(4);
      N.addElement(7);
      N.addElement(3);
      N.removeElement(1);
      N.removeElement(3);
      N.display();

}
