#include <iostream>
#include <map>
#include <string>

using namespace std;

bool code(  const string &FirstString,
            const string &SecondString,
            const string &LastString,
            map<char, int> &cmap,
            bool used[10],
            int k,         //size of the first string
            int p,         //size of the second string
            int q,         //size of the last string
            int r,         //rest from mathematical activity
            char Tokken)
{

    if (k < 0 && p < 0 && q < 0)
        return (r == 0
                && (FirstString.size() == 1 || cmap[FirstString[0]] != 0)
                && (SecondString.size() == 1 || cmap[SecondString[0]] != 0)
                && (LastString.size() == 1 || cmap[LastString[0]] != 0));

    if (k >= 0 && cmap.count(FirstString.at(k)) == 0)
    {
        for (int i = 0; i < 10; ++i)
        {
            if (used[i])
                continue;
            used[i] = true;
            cmap[FirstString.at(k)] = i;
            if ( code(FirstString, SecondString, LastString, cmap, used, k, p, q, r, Tokken) )
                return true;
            cmap.erase(FirstString.at(k));
            used[i] = false;
        }
    }
    else
    {
        if (p >= 0 && cmap.count(SecondString.at(p)) == 0)
        {
            for (int i = 0; i < 10; ++i)
            {
                if (used[i])
                    continue;
                used[i] = true;
                cmap[SecondString.at(p)] = i;
                if (code(FirstString, SecondString, LastString, cmap, used, k, p, q, r, Tokken))
                    return true;
                cmap.erase(SecondString.at(p));
                used[i] = false;
            }
        }
        else
        {
            int num1 = (k >= 0 ? cmap[FirstString.at(k)] : 0);
            int num2 = (p >= 0 ? cmap[SecondString.at(p)] : 0);

            int num0 = (Tokken == '+' ? (num1 + num2) : num1 - num2) + r;
            int rest = (num0 >= 10 ? 1 : (num0 < 0 ? -1 : 0));
            num0 = (num0 + 10) % 10;

            if (q < 0)
            {
                if (num0 != 0)
                    return false;
                return code(FirstString, SecondString, LastString, cmap, used, k - 1, p - 1, q - 1, rest, Tokken);
            }
            else
            {
                if (cmap.count(LastString.at(q)) == 1)
                {
                    if (cmap[LastString.at(q)] == num0)
                        if (code(FirstString, SecondString, LastString, cmap, used, k - 1, p - 1, q - 1, rest, Tokken))
                            return true;
                }
                else
                {
                    if (!used[num0])
                    {
                        used[num0] = true;
                        cmap[LastString.at(q)] = num0;
                        if (code(FirstString, SecondString, LastString, cmap, used, k - 1, p - 1, q - 1, rest, Tokken))
                            return true;
                        cmap.erase(LastString.at(q));
                        used[num0] = false;
                    }
                }
            }
        }
    }

    return false;
}

void printf(const string& FirstString,
            const string& SecondString,
            const string& LastString,
            map<char, int> &cmap,
            char Tokken)
{
    for(int i=0;i<FirstString.size();i++)
        cout<<cmap[FirstString.at(i)];

    cout<<Tokken;

    for(int i=0;i<SecondString.size();i++)
        cout<<cmap[SecondString.at(i)];

    cout<<"=";

    for(int i=0;i<LastString.size();i++)
        cout<<cmap[LastString.at(i)];

    cout<<"\n";
}

int main() {

	string FirstString,SecondString,LastString;
	map<char, int> cmap;
    bool used[10] = {false};
	char Tokken;

	cin>>FirstString;
	cin>>Tokken;
	cin>>SecondString;
	cin>>LastString;

    if (!code(FirstString, SecondString, LastString, cmap, used, FirstString.size() - 1, SecondString.size() - 1, LastString.size() - 1, 0, Tokken))
        return 1;

    printf(FirstString, SecondString, LastString, cmap, Tokken);

	return 0;
}
