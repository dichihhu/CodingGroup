// uva403.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

template <class T>
const T& min(const T& a, const T& b)
{
    return ((a < b) ? a : b);
}
// Command -- Parser --> Script
// Font -- Script --> Bitmap representation
// Ordered Bitmap representation -- renderer + FONTs --> Page

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

class C5TYPE
{
public:
    C5TYPE() : c(5, vector<char>(6, '.')) {};
    vector<vector<char>> c;
};
static C5TYPE C5A({ { '.', '*', '*', '*', '.', '.' },
                    { '*', '.', '.', '.', '*', '.' },
                    { '.', '*', '*', '*', '.', '.' },
                    { '.', '*', '*', '*', '.', '.' },
                    { '.', '*', '*', '*', '.', '.' }
});


static map<char, char> rawfont1({ { 'a', "a" }, {'b', "b"});
static map<char, C5TYPE> rawfontc5({ { 'a', C5A }, { 'b', C5B } });


template <typename T>
struct FontData<T>
{
    FontName _name;
    map<char, T> _data;
    FontData(FontName f) : _name(f) : _data(map<char, T>) {};
};

template<typename T>
class Font<T> {
public:
private:
    map<FontName, FontData<T&>> alpha;
};


static map<string, Opcode> OPCODE({ { ".P", P }, { ".L", L }, { ".R", R }, { ".C", C }, { ".EOP", EOP } });
static map<string, FontName> FONTNAME({ { "C1", C1 }, { "C5", C5 } });
static Font<C1> ;

class textscript
{
public:
    textscript() : _col(0), _row(0), _op(NOP), _text()
    {}
    size_t size() const { return _text.size(); }
    const string& text() const { return _text; }
    Opcode opcode() const { return _op; }
    FontName fontname() { return _font; }
    size_t col() const { return _col; }
    size_t row() const { return _row; }
    void set_font(string s) { _font = FONTNAME[s]; }
    void set_op(string s) { _op = OPCODE[s]; }
    void set_row(size_t r) { _row = r; }
    void set_col(size_t c) { _col = c; }

private:
    Opcode _op;
    FontName _font;
    size_t _row;
    size_t _col;
    string _text;
};


class Bitmap
{
public:
    Bitmap(size_t w, size_t h) : 
        _w(w), _h(h), 
        data(h, vector<char>(w, '.'))
    {}
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
        _start_row(1)
    {};

    Opcode align() const { return _align; }
    size_t start_col() const { return _start_col; }
    size_t start_row() const { return _start_row; }
    void set_align(Opcode op) { _align = op; }
    void set_start_col(size_t c) { _start_col = c; }
    void set_start_row(size_t r) { _start_row = r; }
    void putdata(FontName f, const string& s) { ? ? ? };
private:
    Opcode _align;
    size_t _start_col;
    size_t _start_row;
};

class Page : public Bitmap
{
public:
    Page(size_t w, size_t h) : 
        Bitmap(w, h),
        _col(1), _row(1)
    {}
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
    friend ostream& operator<<(ostream& out, const Page& p)
    {
        for (auto& row : p.data)
        {
            for (auto& c : row)
            {
                out << c;
            }
        }
        return out;
    }
private:
    size_t _col;
    size_t _row;
};

void BuildBitmap(const Script& s, vector<TextBitmap>& vtb)
{
    for (textscript& ts : s.fullscript())
    {
        size_t width = Font::info(ts.fontname()).w() * ts.size();
        size_t height = ts.font().h();

        TextBitmap t(width, height);
        t.set_align(ts.opcode());
        t.set_start_col(ts.col());
        t.set_start_row(ts.row());
        t.putdata(ts.fontname(), ts.text());//???
        vtb.push_back(t);
    }
}

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
        dst_col = (p.w() - t.w()) > 0 ? (p.w() - t.w() + 1) : 1;
        dst_row = t.start_row();
        src_x = (p.w() - t.w()) > 0 ? 1 : (t.w() - p.w() + 1);
        src_y = 1;
        break;
    case C:
        dst_col = (p.w() - t.w()) > 0 ? ((p.w() - t.w()) / 2) + 1 : 1;
        dst_row = t.start_row();
        src_x = (p.w() - t.w()) > 0 ? 1 : ((t.w() - p.w()) / 2) + 1;
        src_y = 1;
        break;
    }

    int dst_w = p.w() - dst_col + 1;
    int dst_h = p.h() - dst_row + 1;

    int end_of_draw_w = min<size_t>(t.w() - src_x + 1, dst_w);
    int end_of_draw_h = min<size_t>(t.h() - src_y + 1, dst_h);

    for (int j = 0; j < end_of_draw_h; j++)
    {
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

Page layout(const vector<TextBitmap>& vtb, Page& p)
{
    for (TextBitmap line : vtb)
    {
        draw(line, p);
    }
    return p;
}

int main(int argc, char* argv[])
{
    Script s;
    parse(cin, s);
    
    vector<TextBitmap> vtb;
    BuildBitmap(s, vtb);

    Page p(60, 60);
    cout << layout(vtb, p);


	return 0;
}

