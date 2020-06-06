#include <TGUI/TGUI.hpp>
#include <iostream>
#include <fstream>
#include "Book.h"
#include <atlstr.h>
#undef MessageBox
std::vector<Book> books;
int position = 0;

int main();
void getBooksFromDirectory();
void saveBooksInDirectory();
void init(tgui::Gui& gui);
vector<string> getFiles(CString directory);

int main()
{
    sf::RenderWindow window{ {800, 500}, "Book Reviews" };
    
    tgui::Gui gui{ window }; // Create the gui and attach it to the window
    tgui::Theme theme{ "Themes/Black.txt" };
    tgui::Theme::setDefault(&theme);
    getBooksFromDirectory();
    init(gui);

    sf::Texture texture;
    texture.loadFromFile("Images/background1.jpg");
    sf::Sprite background;
    background.setTexture(texture);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                saveBooksInDirectory();
                window.close();
            }

            gui.handleEvent(event); // Pass the event to the widgets
        }

        window.clear(); 
        window.draw(background);
        gui.draw(); // Draw all widgets
        window.display();
    }

}

void saveBooksInDirectory() 
{
    //delete all files in directory before saving them again
    vector<string> files = getFiles("Data/");
    for (auto fileName : files)
    {
        const int result = remove(fileName.c_str());
    }

    for (auto &book : books)
    {
        ofstream file("Data/" + book.GetTitle() + ".txt");
        file << "Title:" + book.GetTitle() << endl;
        file << "Author:" + book.GetAuthor() << endl;
        file << "Pages:" + book.GetPages() << endl;
        file << "ISBN:" + book.GetISBN() << endl;
        file << "Review:" + book.GetReview() << endl;
    }
}

void getBooksFromDirectory() 
{
    vector<string> files = getFiles("Data/");
    for (auto fileName : files)
    {
        ifstream file(fileName);
        if (file.is_open())
        {
            string line;
            Book book;
            while (getline(file, line))
            {
                if (line.find("Title") != std::string::npos)
                {
                    string title = line.substr(line.find(":") + 1);
                    book.SetTitle(title);
                }
                if (line.find("Author") != std::string::npos)
                {
                    string author = line.substr(line.find(":") + 1);
                    book.SetAuthor(author);
                }
                if (line.find("Pages") != std::string::npos)
                {
                    string pages = line.substr(line.find(":") + 1);
                    book.SetPages(pages);
                }
                if (line.find("ISBN") != std::string::npos)
                {
                    string ISBN = line.substr(line.find(":") + 1);
                    book.SetISBN(ISBN);
                }
                if (line.find("Review") != std::string::npos)
                {
                    string review = line.substr(line.find(":") + 1);
                    while (getline(file, line))
                    {
                        review += "\n" + line;
                    }
                    book.SetReview(review);
                }

            }
            books.push_back(book);
        }  
    }
}

void SetNextBook(tgui::EditBox::Ptr title, tgui::EditBox::Ptr author, tgui::EditBox::Ptr pages, tgui::EditBox::Ptr isbn, tgui::TextBox::Ptr review)
{
    if ((position < books.size() - 1) && books.size() > 0)
    {
        ++position;
        title->setText(books[position].GetTitle());
        author->setText(books[position].GetAuthor());
        pages->setText(books[position].GetPages());
        isbn->setText(books[position].GetISBN());
        review->setText(books[position].GetReview());
    }
    
   

}

void SetPreviousBook(tgui::EditBox::Ptr title, tgui::EditBox::Ptr author, tgui::EditBox::Ptr pages, tgui::EditBox::Ptr isbn, tgui::TextBox::Ptr review)
{
    if (position > 0 && books.size() > 0)
    {
        --position;
        title->setText(books[position].GetTitle());
        author->setText(books[position].GetAuthor());
        pages->setText(books[position].GetPages());
        isbn->setText(books[position].GetISBN());
        review->setText(books[position].GetReview());
    }
  
   

}

void AddBook(tgui::EditBox::Ptr title, tgui::EditBox::Ptr author, tgui::EditBox::Ptr pages, tgui::EditBox::Ptr isbn, tgui::TextBox::Ptr review, tgui::MessageBox::Ptr messageAdd)
{
    Book book = Book();
    book.SetTitle(title->getText().toAnsiString());
    book.SetAuthor(author->getText().toAnsiString());
    book.SetPages(pages->getText().toAnsiString());
    book.SetISBN(isbn->getText().toAnsiString());
    book.SetReview(review->getText().toAnsiString());
    books.push_back(book);
    position = books.size() - 1;
    messageAdd->setVisible(true);
   }

void DeleteBook(tgui::EditBox::Ptr title, tgui::EditBox::Ptr author, tgui::EditBox::Ptr pages, tgui::EditBox::Ptr isbn, tgui::TextBox::Ptr review, tgui::MessageBox::Ptr messageDelete)
{
    for (std::vector<Book>::iterator itr = books.begin(); itr != books.end(); )
    {
        if (itr->GetTitle() == title->getText().toAnsiString())
        {
            itr = books.erase(itr);
            messageDelete->setVisible(true);
        }
        else
            ++itr;
    }
}

void init(tgui::Gui &gui)
{
    //Title
    tgui::Label::Ptr lblTitle = tgui::Label::create("Title");
    gui.add(lblTitle);
    lblTitle->setSize("10%","5%");
    lblTitle->setPosition("10%","10%");
    lblTitle->setTextSize(15);
    
    tgui::EditBox::Ptr editTitle = tgui::EditBox::create();
    gui.add(editTitle);
    editTitle->setSize("30%", "5%");
    editTitle->setPosition("20%", "10%");

    //Author
    tgui::Label::Ptr lblAuthor = tgui::Label::create("Author");
    gui.add(lblAuthor);
    lblAuthor->setSize("10%", "5%");
    lblAuthor->setPosition("10%", "20%"); 
    lblAuthor->setTextSize(15);

    tgui::EditBox::Ptr editAuthor = tgui::EditBox::create();
    gui.add(editAuthor);
    editAuthor->setSize("30%", "5%");
    editAuthor->setPosition("20%", "20%");

    //Pages
    tgui::Label::Ptr lblPages = tgui::Label::create("Pages");
    gui.add(lblPages);
    lblPages->setSize("10%", "5%");
    lblPages->setPosition("10%", "30%");
    lblPages->setTextSize(15);

    tgui::EditBox::Ptr editPages = tgui::EditBox::create();
    gui.add(editPages);
    editPages->setSize("30%", "5%");
    editPages->setPosition("20%", "30%");

    //ISBN
    tgui::Label::Ptr lblISBN = tgui::Label::create("ISBN");
    gui.add(lblISBN);
    lblISBN->setSize("10%", "5%");
    lblISBN->setPosition("10%", "40%");
    lblISBN->setTextSize(15);

    tgui::EditBox::Ptr editISBN = tgui::EditBox::create();
    gui.add(editISBN);
    editISBN->setSize("30%", "5%");
    editISBN->setPosition("20%", "40%");
    
    //Review
    tgui::Label::Ptr lblReview = tgui::Label::create("Review");
    gui.add(lblReview);
    lblReview->setSize("10%", "5%");
    lblReview->setPosition("10%", "50%");
    lblReview->setTextSize(15);

    tgui::TextBox::Ptr editReview = tgui::TextBox::create();
    gui.add(editReview);
    editReview->setSize("60%", "30%");
    editReview->setPosition("20%", "50%");
    
    //Create MessageBoxes
    tgui::MessageBox::Ptr messageAdd = tgui::MessageBox::create("Add", "Book added successfully!", { "OK" });
    messageAdd->setPosition("30%", "30%");
    messageAdd->setVisible(false);
    messageAdd->onButtonPress([=]() { messageAdd->setVisible(false); });
    gui.add(messageAdd);

    tgui::MessageBox::Ptr messageDelete = tgui::MessageBox::create("Delete", "Book deleted successfully!", { "OK" });
    messageDelete->setPosition("30%", "30%");
    messageDelete->setVisible(false);
    messageDelete->onButtonPress([=]() { messageDelete->setVisible(false); });
    gui.add(messageDelete);

    //Buttons
    tgui::Button::Ptr btnNext = tgui::Button::create("Next");
    gui.add(btnNext);
    btnNext->onPress(SetNextBook, editTitle, editAuthor, editPages, editISBN, editReview);
    btnNext->setSize("10%", "5%");
    btnNext->setPosition("10%", "90%");

    tgui::Button::Ptr btnPrevious = tgui::Button::create("Previous");
    gui.add(btnPrevious);
    btnPrevious->onPress(SetPreviousBook, editTitle, editAuthor, editPages, editISBN, editReview);
    btnPrevious->setSize("10%", "5%");
    btnPrevious->setPosition("30%", "90%");

    tgui::Button::Ptr btnAdd = tgui::Button::create("Add");
    gui.add(btnAdd);
    btnAdd->onPress(AddBook, editTitle, editAuthor, editPages, editISBN, editReview, messageAdd);
    btnAdd->setSize("10%", "5%");
    btnAdd->setPosition("50%", "90%");

    tgui::Button::Ptr btnDelete = tgui::Button::create("Delete");
    gui.add(btnDelete);
    btnDelete->onPress(DeleteBook, editTitle, editAuthor, editPages, editISBN, editReview, messageDelete);
    btnDelete->setSize("10%", "5%");
    btnDelete->setPosition("70%", "90%");

   
    //Add first book details if exists
    if (books.size() > 0)
    {
        editTitle->setText(books[0].GetTitle());
        editAuthor->setText(books[0].GetAuthor());
        editPages->setText(books[0].GetPages());
        editISBN->setText(books[0].GetISBN());
        editReview->setText(books[0].GetReview());
    }
}

vector<string> getFiles(CString directory)
{
    vector<string> files;
    HANDLE dir;
    WIN32_FIND_DATA file_data;
    CString  file_name, full_file_name;
    if ((dir = FindFirstFile((directory + "/*"), &file_data)) == INVALID_HANDLE_VALUE)
    {
        // Invalid directory
    }
    while (FindNextFile(dir, &file_data)) {
        file_name = file_data.cFileName;
        full_file_name = directory + file_name;
        std::string str = std::string(CStringA(full_file_name));
        if (str.find(".txt") != std::string::npos)
            files.push_back(str);
    }
    return files;
}