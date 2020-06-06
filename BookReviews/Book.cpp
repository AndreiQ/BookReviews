#include "Book.h"
using namespace std;
 Book::Book() 
{


}
void Book::SetTitle(string title)
{
	this->Title = title;
}

void Book::SetAuthor(string author)
{
	this->Author = author;
}

void Book::SetPages(string pages)
{
	this->NumberOfPages = pages;
}

void Book::SetISBN(string isbn)
{
	this->ISBN = isbn;
}

void Book::SetReview(string review)
{
	this->Review = review;
}

string Book::GetTitle()
{
	return this->Title;
}

string Book::GetAuthor()
{
	return this->Author;
}

string Book::GetPages()
{
	return this->NumberOfPages;
}

string Book::GetISBN()
{
	return this->ISBN;
}

string Book::GetReview()
{
	return this->Review;
}
