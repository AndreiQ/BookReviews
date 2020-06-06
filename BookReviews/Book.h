#pragma once
#include <string>
using namespace std;

class Book {
private:
    string Title;
    string Author;
    string NumberOfPages;
    string ISBN;
    string Review;
public:
    void SetTitle(string title);
    void SetAuthor(string author);
    void SetPages(string pages);
    void SetISBN(string isbn);
    void SetReview(string review);
    string GetTitle();
    string GetAuthor();
    string GetPages();
    string GetISBN();
    string GetReview();
    Book();


};