#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    int arr[10] = { 6345, 567, 1435, 7453, 567, 65, 745, 1123, 1598, 5 };
    int mask = 255; //маска 0000 0000 1111 1111
    int i = 0;

    cout << "Данный массив: ";
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
       
    cout << endl << "Новый массив: ";
    for (i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            cout << arr[i] << " ";
        }
        else 
        {
            arr[i] = arr[i] ^ mask;
            cout << arr[i] << " ";
        }
    }

    cout << endl;

    system("pause");
    return 0;
}
