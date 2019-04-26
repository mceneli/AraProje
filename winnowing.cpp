// compilation: g++ winnowing.cpp -lstdc++fs

/*
    MOSS Algoritmasının Uygulaması:

    1. Kodun iskeletinin çıkarılması:
        - Yorumlar temizlenir.
        - Fazla boşluklar temizlenir.
        - String içleri temizlenir.
        - Kod dönüşümü yapılır.
    2. Winnowing algoritmasının uygulanması:
        - Parmak izleri oluşturulur.
        - Karp-Rabin algoritması ile hash'leme yapılır.
        - Winnowing algoritması ile parmak izleri seçilir.
    3. Parmak izlerinin karşılaştırmaları.
*/

/*
    x = y+5 -> _v_=_v_+_v_
    for (...), while (...) -> _l_()
    if (...), else if (...), else (...), switch-case: _c_()
    func(x, y) -> _f_(_p_,_p_)
*/

/*
    Tamamlananlar:
    + değişken tanımlamaları
    + fonksiyon tanımlamaları
    + koşullu ifadeler
    + döngüler
    + işlemler
    + noktalı virgüller
    + virgüller
    + diziler: A[]
    + goto, label
    + struct'lar
    + typedef'ler
    + struct erişimleri: ".", "->"

    Eksiklikler:
    - define ile oluşturulan macro'lar
    - define ile tip atamaları (örn: #define int sayi) 
    - undef, ifdef vs...
    - Ternary operatörü (örn: return x > 0 ? true : false)
    - C'nin standart olmayan kütüphanelerinin fonksiyonları
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <experimental/filesystem>

#include "transformCode.hpp"

struct Code
{
    std::string skeleton, fileName;
    std::map <std::string, int> fingerprints;
};

std::vector <Code> getCodes(std::string &path, int k);
int compareCodes(Code *code1, Code *code2);
int main()
{
    std::string path = "dataset";

    initializeSets();

    int k = 10;
    std::vector <Code> codes = getCodes(path, k);

    for (Code &code: codes)
        std::cout << code.fileName << ":\n" << code.skeleton << "\n\n" << std::endl;

    for (int i = 0; i < codes.size()-1; ++i)
    {
        for (int j = i+1; j < codes.size(); ++j)
        {
            double diff = compareCodes(&codes[i], &codes[j]);
            int rate1 = 100 * diff / (codes[i].skeleton.size() - k + 1);
            int rate2 = 100 * diff / (codes[j].skeleton.size() - k + 1);
            std::cout << "similarity of " << codes[i].fileName << " to " << codes[j].fileName << ": " << rate1 << "\n";
            std::cout << "similarity of " << codes[j].fileName << " to " << codes[i].fileName << ": " << rate2 << "\n\n";
        }
    }

    return 0;
}

std::string getCodeSkeleton(const std::string &path);
std::map <std::string, int> getFingerprints(const std::string &codeSkeleton, int k);
std::vector <Code> getCodes(std::string &path, int k)
{
    std::vector <Code> codes;

    for (const auto &codeFile: std::experimental::filesystem::directory_iterator(path))
    {
        Code *code = new Code;
        code->fileName = codeFile.path();
        code->skeleton = getCodeSkeleton(code->fileName);
        code->fingerprints = getFingerprints(code->skeleton, k);
        codes.push_back(*code);
    }

    return codes;
}

std::string getCodeSkeleton(const std::string &path)
{
    std::string fullCode = removeComments(path);
    fullCode = removeSpaces(fullCode);
    removeQuotes(fullCode);
    return transformCode(fullCode);
}

std::map <std::string, int> getFingerprints(const std::string &codeSkeleton, int k)
{
    std::map <std::string, int> fingerprints;

    for (int i = 0; i <= codeSkeleton.size() - k; ++i)
        ++fingerprints[codeSkeleton.substr(i, k)];
    
    return fingerprints;
}

int compareCodes(Code *code1, Code *code2)
{
    int tokens_matched = 0;

    for (const auto &p1: code1->fingerprints)
    {
        auto p2 = code2->fingerprints.find(p1.first);

        if (p2 != code2->fingerprints.end())
            tokens_matched += std::min(p1.second, p2->second);
    }

    return tokens_matched;
}