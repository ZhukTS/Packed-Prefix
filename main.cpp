//https://contest.yandex.ru/contest/26133/run-report/128495803/

/*
    Алгоритм
        1. Чтаем строки
        2. Распаковываем первую строку в переменную prefix
        3. Распаковываем следующую строку посимвольно сравнивая с prefix, как только нашли несоответствие обрезаем prefix и переходим к следующей строке
        4. Выводим результат
    Сложность
        n - количество строк
        m - длинна 1-ой строки в распакованном виде
            Зависимость длинны распакованной строки от запакованной - экспоненциальная
        p - длинна префикса
        Временная
            O(n * m) - в худшем случае
            O(n * p) - в лучшем случае
        Пространственная
            O(m)
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string unpack(const string& s, const string& currentPrefix = "")
{
    string result;
    int i = 0;
    size_t maxLength = currentPrefix.size();
    while (i < s.size() && (currentPrefix.empty() || result.size() < maxLength))
    {
        if (isalpha(s[i]))
        {
            if (!currentPrefix.empty() && 
                (result.size() >= maxLength || s[i] != currentPrefix[result.size()]))
            {
                return result;
            }
            result += s[i];
            ++i;
        }
        else if (isdigit(s[i]))
        {
            int repeatCount = s[i] - '0';
            ++i;
            if (s[i] == '[')
            {
                int bracketBalance = 1;
                ++i;
                int start = i;
                while (i < s.size() && bracketBalance > 0)
                {
                    if (s[i] == '[') ++bracketBalance;
                    if (s[i] == ']') --bracketBalance;
                    ++i;
                }
                string innerStr = unpack(s.substr(start, i - start - 1), currentPrefix.empty() ? "" : currentPrefix.substr(result.size()));
                while (repeatCount-- && (currentPrefix.empty() || result.size() < maxLength))
                {
                    for (char c : innerStr)
                    {
                        if (!currentPrefix.empty() && 
                            (result.size() >= maxLength || c != currentPrefix[result.size()]))
                        {
                            return result;
                        }
                        result += c;
                    }
                }
            }
        }
    }
    return result;
}

int main()
{
    int n;
    cin >> n;
    vector<string> packedStrings(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> packedStrings[i];
    }
    string prefix = unpack(packedStrings[0]);
    for (int i = 1; i < n; ++i)
    {
        prefix = unpack(packedStrings[i], prefix);
        if (prefix.empty()) break;
    }
    cout << prefix;
}