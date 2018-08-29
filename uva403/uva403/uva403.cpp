// uva403.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Command -- Parser --> Script
// Font -- Script --> Bitmap representation
// Ordered Bitmap -- renderer + buffer --> Page
enum Opcode {
    NOP,
    P, // font row col string
    L, // font row 1   string
    R, // font row 1   string
    C, // font row 1   string
    EOP // (blank)
};

enum FontName {
    NA,
    C1,
    C5
};

class Script {
public:

    struct ScriptLine {
        Opcode op;
        FontName font;
        size_t row;
        size_t col;
        string text;
        ScriptLine() : op(NOP), font(NA), row(0), col(0), text("") {};
    };

    Script() :
        MapOpcode({ { ".P", P }, { ".L", L }, { ".R", R }, { ".C", C }, { ".EOP", EOP } }),
        MapFontName({ { "C1", C1 }, { "C5", C5 } }),
        s(0)
    {        
    };

private:
    const map<string, Opcode> MapOpcode;
    const map<string, FontName> MapFontName;
    vector<ScriptLine> s;
};

bool Parser(istream& in, Script& s)
{
    string str;
    while (getline(in, str))
    {
        ScriptLine ln = parseline(str);
        s.AddLine(ln);
    }
    return true;
}


template<typename T>
class alphabet
{
    size_t width;
    size_t height;
    map<char, T> bitmap;
public:
    alphabet(size_t w, size_t h, FontName name) : width(w), height)(h)
    {
        switch (FontName)
        {
        C1:
            for (int i = 0; i < 26; i++) bitmap['a' + i] = 'a' + i;
            bitmap[' '] = ' ';
        C5:
            for (int i = 0; i < 26; i++) bitmap['a' + i] = ;
            bitmap[' '] = ' ';
        };
    }
};

template<typename T>
map<char, T> Font;


class PostScriptLine
{

public:
    vector<PostScriptLine> parser(istream& in);

};


class Bitmap
{
public:
    Bitmap(size_t w, size_t h) : 
        _w(w), _h(h), 
        data(h, vector<char>(w, '.'))
    {};

    size_t w() const { return _w; }
    size_t h() const { return _h; }
    char& at(size_t x, size_t y) 
    {
        return data.at(y).at(x);
    }
    const char& at(size_t x, size_t y) const
    {
        return data.at(y).at(x);
    }

private:
    size_t _w;
    size_t _h;
    vector<vector<char>> data;
};

class TextBitmap : public Bitmap
{
public:
    TextBitmap(size_t w, size_t h) :
        Bitmap(w, h),
        _align(NOP),
        _start_col(1),
        _start_row(1),
        _src_w(0),
        _src_h(0)
    {};

    Opcode align() const { return _align; }
    size_t start_col() const { return _start_col; }
    size_t start_row() const { return _start_row; }
    size_t src_w() const { return _src_w; }
    size_t src_h() const { return _src_h; }
    void set_align(Opcode op) { _align = op; }
    void set_start_col(size_t c) { _start_col = c; }
    void set_start_row(size_t r) { _start_row = r; }
    void set_src_w(size_t w) { _src_w = w; }
    void set_src_h(size_t h) { _src_h = h; }
private:
    Opcode _align;
    size_t _start_col;
    size_t _start_row;
    size_t _src_w;
    size_t _src_h;
};

class Page : public Bitmap
{
public:
    Page(size_t w, size_t h) : 
        Bitmap(w, h),
        _col(1), _row(1)
    {};
    size_t col() const { return _col; }
    size_t row() const { return _row; }
    void set_col(size_t c) { _col = c; }
    void set_row(size_t r) { _row = r; }
    void carriagereturn()
    {
        set_col(1);
        set_row(row() + 1);
    }
    void putpoint(const char& c, size_t col, size_t row)
    {
        set_col(col);
        set_row(row);
        at(col, row) = c;
    }
private:
    size_t _col;
    size_t _row;
};

// ------     ............
// |    |     ............
// ------     ............
//            ............

void draw(const TextBitmap& t, Page& p)
{
    size_t dst_col = 0;
    size_t dst_row = 0;
    size_t src_x = 0;
    size_t src_y = 0;
    switch (t.align())
    {
    case P:
        dst_col = p.col();
        dst_row = t.start_row();
        src_x = 1;
        src_y = 1;
        break;
    case L:
        dst_col = 1;
        dst_row = t.start_row();
        src_x = 1;
        src_y = 1;
        break;
    case R:
        dst_col = (p.w() - t.src_w()) > 0 ? (p.w() - t.src_w() + 1) : 1;
        dst_row = t.start_row();
        src_x = (p.w() - t.src_w()) > 0 ? 1 : (t.src_w() - p.w() + 1);
        src_y = 1;
        break;
    case C:
        dst_col = (p.w() - t.src_w()) > 0 ? ((p.w() - t.src_w()) / 2) + 1 : 1;
        dst_row = t.start_row();
        src_x = (p.w() - t.src_w()) > 0 ? 1 : ((t.src_w() - p.w()) / 2) + 1;
        src_y = 1;
        break;
    }

    int dst_w = p.w() - dst_col + 1;
    int dst_h = p.h() - dst_row + 1;

    int end_of_draw_w = min(t.src_w() - src_x + 1, dst_w);
    int end_of_draw_h = min(t.src_h() - src_y + 1, dst_h);

    for (int j = 0; j < end_of_draw_h; j++)
    {
        //p.putline(l.data[src_y], src_x, end_of_draw_w);
        for (int i = 0; i < end_of_draw_w; i++)
        {
            p.putpoint(t.at(src_x, src_y), dst_col, dst_row);
            src_x++;
            dst_col++;
        }
        p.carriagereturn();
        src_y++;
        dst_row++;
    }    
}

Page layout(const Bitmap& b)
{
    Page p(60, 60);
    BitmapLine line;

    while (b.getline(line))
    {
        draw(line, p);
    }
    return p;
}

int main(int argc, char* argv[])
{
    Script s;
    parse(cin, s);
    
    Bitmap b;
    buildbitmap(s, b);

    cout << layout(b);


	return 0;
}

