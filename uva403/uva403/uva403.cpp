// uva403.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

enum FontName {
    NA,
    C1,
    C5
};
typedef vector<vector<char>> FTYPE;
static const FTYPE C1A{ { 'A' } }, C1B{ { 'B' } }, C1C{ { 'C' } }, C1D{ { 'D' } }, C1E{ { 'E' } }, C1F{ { 'F' } },
C1G{ { 'G' } }, C1H{ { 'H' } }, C1I{ { 'I' } }, C1J{ { 'J' } }, C1K{ { 'K' } }, C1L{ { 'L' } }, C1M{ { 'M' } },
C1N{ { 'N' } }, C1O{ { 'O' } }, C1P{ { 'P' } }, C1Q{ { 'Q' } }, C1R{ { 'R' } }, C1S{ { 'S' } }, C1T{ { 'T' } },
C1U{ { 'U' } }, C1V{ { 'V' } }, C1W{ { 'W' } }, C1X{ { 'X' } }, C1Y{ { 'Y' } }, C1Z{ { 'Z' } }, C1BLANK{ { ' ' } };
typedef vector<char> C5Stroke;
static const C5Stroke D1S3D2{ '.', '*', '*', '*', '.', '.' };
static const C5Stroke S1D3S1D1{ '*', '.', '.', '.', '*', '.' };
static const C5Stroke S5D1{ '*', '*', '*', '*', '*', '.' };
static const C5Stroke S4D2{ '*', '*', '*', '*', '.', '.' };
static const C5Stroke D1S4D1{ '.', '*', '*', '*', '*', '.' };
static const C5Stroke S1D5{ '*', '.', '.', '.', '.', '.' };
static const C5Stroke D1S4D1{ '.', '*', '*', '*', '*', '.' };
static const C5Stroke S3D3{ '*', '*', '*', '.', '.', '.' };
static const C5Stroke S1D2S2D1{ '*', '.', '.', '*', '*', '.' };
static const C5Stroke D2S1D3{ '.', '.', '*', '.', '.', '.' };
static const C5Stroke D2S3D1{ '.', '.', '*', '*', '*', '.' };
static const C5Stroke D3S1D2{ '.', '.', '.', '*', '.', '.' };
static const C5Stroke S1D2S1D2{ '*', '.', '.', '*', '.', '.' };
static const C5Stroke D1S2D3{ '.', '*', '*', '.', '.', '.' };
static const C5Stroke S2D1S2D1{ '*', '*', '.', '*', '*', '.' };
static const C5Stroke S1D1S1D1S1D1{ '*', '.', '*', '.', '*', '.' };
static const C5Stroke D4S1D1{ '.', '.', '.', '.', '*', '.' };
static const C5Stroke D1S1D1S1D2{ '.', '*', '.', '*', '.', '.' };
static const C5Stroke D1S1D4{ '.', '*', '.', '.', '.', '.' };
static const C5Stroke D6{ '.', '.', '.', '.', '.', '.' };
static const FTYPE C5A{ D1S3D2, S1D3S1D1, S5D1, S1D3S1D1, S1D3S1D1 };
static const FTYPE C5B{ S4D2, S1D3S1D1, S4D2, S1D3S1D1, S4D2 };
static const FTYPE C5C{ D1S4D1, S1D3S1D1, S1D5, S1D5, D1S4D1 };
static const FTYPE C5D{ S4D2, S1D3S1D1, S1D3S1D1, S1D3S1D1, S4D2 };
static const FTYPE C5E{ S5D1, S1D5, S3D3, S1D5, S5D1 };
static const FTYPE C5F{ S5D1, S1D5, S3D3, S1D5, S1D5 };
static const FTYPE C5G{ D1S4D1, S1D5, S1D2S2D1, S1D3S1D1, D1S3D2 };
static const FTYPE C5H{ S1D3S1D1, S1D3S1D1, S5D1, S1D3S1D1, S1D3S1D1 };
static const FTYPE C5I{ S5D1, D2S1D3, D2S1D3, D2S1D3, S5D1 };
static const FTYPE C5J{ D2S3D1, D3S1D2, D3S1D2, S1D2S1D2, D1S2D3 };
static const FTYPE C5K{ S1D3S1D1, S1D2S1D2, S3D3, S1D2S1D2, S1D3S1D1 };
static const FTYPE C5L{ S1D5, S1D5, S1D5, S1D5, S5D1 };
static const FTYPE C5M{ S1D3S1D1, S2D1S2D1, S1D1S1D1S1D1, S1D3S1D1, S1D3S1D1 };
static const FTYPE C5N{ S1D3S1D1, S1D2S2D1, S1D1S1D1S1D1, S1D2S2D1, S1D3S1D1 };
static const FTYPE C5O{ D1S3D2, S1D3S1D1, S1D3S1D1, S1D3S1D1, D1S3D2 };
static const FTYPE C5P{ S4D2, S1D3S1D1, S4D2, S1D5, S1D5 };
static const FTYPE C5Q{ D1S3D2, S1D3S1D1, S1D3S1D1, S1D2S2D1, D1S4D1 };
static const FTYPE C5R{ S4D2, S1D3S1D1, S4D2, S1D2S1D2, S1D3S1D1 };
static const FTYPE C5S{ D1S4D1, S1D5, D1S3D2, D4S1D1, S4D2 };
static const FTYPE C5T{ S5D1, S1D1S1D1S1D1, D2S1D3, D2S1D3, D1S3D2 };
static const FTYPE C5U{ S1D3S1D1, S1D3S1D1, S1D3S1D1, S1D3S1D1, D1S3D2 };
static const FTYPE C5V{ S1D3S1D1, S1D3S1D1, D1S1D1S1D2, D1S1D1S1D2, D2S1D3 };
static const FTYPE C5W{ S1D3S1D1, S1D3S1D1, S1D1S1D1S1D1, S2D1S2D1, S1D3S1D1 };
static const FTYPE C5X{ S1D3S1D1, D1S1D1S1D2, D2S1D3, D1S1D1S1D2, S1D3S1D1 };
static const FTYPE C5Y{ S1D3S1D1, D1S1D1S1D2, D2S1D3, D2S1D3, D2S1D3 };
static const FTYPE C5Z{ S5D1, D3S1D2, D2S1D3, D1S1D4, S5D1 };
static const FTYPE C5BLANK{ D6, D6, D6, D6, D6 };

static const map<char, FTYPE> MC1({ { 'A', C1A }, { 'B', C1B } });
static const map<char, FTYPE> MC5({ { 'A', C5A }, { 'B', C5B } });

class FontData
{
public:
    FontData(FontName f, map<char, FTYPE> d) : _name(f), _data(d)
    {
        _w = _data.operator[]('A').operator[](0).size();
        _h = _data.operator[]('A').size();
    };
    size_t const w() { return _w; }
    size_t const h() { return _h; }
    FTYPE& const data(const char c) {return _data.at(c);}
private:
    FontName _name;
    map<char, FTYPE> _data;
    size_t _w;
    size_t _h;
};

static const map<FontName, FontData> fontmap{ { C1, FontData(C1, MC1) }, { C5, FontData(C5, MC5) } };

const FontData& GetFontData(FontName name)
{
    return fontmap.at(name);
}

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

static map<string, Opcode> OPCODE({ { ".P", P }, { ".L", L }, { ".R", R }, { ".C", C }, { ".EOP", EOP } });
static map<string, FontName> FONTNAME({ { "C1", C1 }, { "C5", C5 } });

class TextScript
{
public:
    TextScript() : _col(0), _row(0), _op(NOP), _text(), _w(0), _h(0), _start_col(0), _start_row(0)
    {}
    size_t size() const { return _text.size(); }
    const string& text() const { return _text; }
    Opcode opcode() const { return _op; }
    FontName fontname() const { return _font; }
    size_t col() const { return _col; }
    size_t row() const { return _row; }
    size_t w() const { return _w; }
    size_t h() const { return _h; }
    size_t start_col() const { return _start_col; }
    size_t start_row() const { return _start_row; }
    void set_start_col(size_t c) { _start_col = c; }
    void set_start_row(size_t r) { _start_row = r; }
    void set_font(string s) { _font = FONTNAME[s]; }
    void set_op(string s) { _op = OPCODE[s]; }
    void set_row(size_t r) { _row = r; }
    void set_col(size_t c) { _col = c; }
    void set_w(size_t w) { _w = w; }
    void set_h(size_t h) { _h = h; }
private:
    Opcode _op;
    FontName _font;
    size_t _row;
    size_t _col;
    size_t _w;
    size_t _h;
    string _text;
    size_t _start_col;
    size_t _start_row;
};

class Bitmap
{
public:
    Bitmap(size_t w, size_t h) : 
        _w(w), _h(h), 
        _col(1), _row(1),
        _data(h, vector<char>(w, '.'))
    {}
    size_t w() const { return _w; }
    size_t h() const { return _h; }
    size_t col() const { return _col; }
    size_t row() const { return _row; }
    void set_col(size_t c) { _col = c; }
    void set_row(size_t r) { _row = r; }
    char& at(size_t x, size_t y)
    {
        return _data.at(y).at(x);
    }
    const char& at(size_t x, size_t y) const
    {
        return _data.at(y).at(x);
    }
    void putdata(const vector<vector<char>>& d) { _data = d; }
    void putpoint(const char& c, size_t col, size_t row)
    {
        set_col(col);
        set_row(row);
        at(col, row) = c;
    }
private:
    size_t _w;
    size_t _h;
    size_t _col;
    size_t _row;
    vector<vector<char>> _data;
};

class FontBitmap : public Bitmap
{
public:
    explicit FontBitmap(FTYPE t) :
        Bitmap(t[0].size(), t.size())
    {
        putdata(t);
    }
};

class TextBitmap : public Bitmap
{
public:
    TextBitmap(size_t w, size_t h) :
        Bitmap(w, h),
        _align(NOP),
        _start_col(1),
        _start_row(1)
    {}
    Opcode align() const { return _align; }
    size_t start_col() const { return _start_col; }
    size_t start_row() const { return _start_row; }
    void set_align(Opcode op) { _align = op; }
    void set_start_col(size_t c) { _start_col = c; }
    void set_start_row(size_t r) { _start_row = r; }
//    void putdata(FontName f, const string& s) { ? ? ? };
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

bool Parse(istream& in, Script& s)
{
    string str;
    while (getline(in, str))
    {
        ScriptLine ln = parseline(str);
        s.AddLine(ln);
    }
    return true;
}

void BuildTextBitmap(const Script& s, vector<TextBitmap>& vtb)
{
    for (TextScript& ts : s.fullscript())
    {
        size_t width = Font::info(ts.fontname()).w() * ts.size();
        size_t height = ts.font().h();

        TextBitmap t(width, height);
        t.set_align(ts.opcode());
        t.set_start_col(ts.col());
        t.set_start_row(ts.row());
//        t.putdata(ts.fontname(), ts.text());//???
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
void putcharacter(const TextScript& s, Page& p)
{
    size_t dst_col = 0;
    size_t dst_row = 0;
    size_t src_x = 0;
    size_t src_y = 0;
    switch (s.opcode())
    {
    case P:
        dst_col = p.col();
        dst_row = s.start_row();
        src_x = 0;
        src_y = 0;
        break;
    case L:
        dst_col = 0;
        dst_row = s.start_row();
        src_x = 0;
        src_y = 0;
        break;
    case R:
        dst_col = (p.w() - s.w()) > 0 ? (p.w() - s.w()) : 0;
        dst_row = s.start_row();
        src_x = (p.w() - s.w()) > 0 ? 0 : (s.w() - p.w());
        src_y = 0;
        break;
    case C:
        dst_col = (p.w() - s.w()) > 0 ? ((p.w() - s.w()) / 2) : 0;
        dst_row = s.start_row();
        src_x = (p.w() - s.w()) > 0 ? 0 : ((s.w() - p.w()) / 2);
        src_y = 0;
        break;
    }

    int dst_w = p.w() - dst_col;
    int dst_h = p.h() - dst_row;

    int end_of_draw_w = min<size_t>(s.w() - src_x, dst_w);
    int end_of_draw_h = min<size_t>(s.h() - src_y, dst_h);

    //p.putpoint( /*  find a font for the ch t.at(src_x, src_y)*/, dst_col, dst_row);
    // ..5.....6.....7.....8.....9.....
    //    |                      |
    //    src_x                  src_x+dst_w-1
    //   which ch: (src_x-1)/f_w + 1   0-base: src_x/f_w
    //   which pos: (src_x-1)%f_w + 1  0-base: src_x%f_w
    FontData f = GetFontData(s.fontname());
    size_t start_c = src_x / f.w();

    for (int c = start_c; c < s.text().size(); c++)
    {
        FontBitmap fb = FontBitmap(f.data(s.text()[c]));
        size_t start_bit = src_x % f.w();
        src_x =
            putFontBitmap(fb, start_bit, src_y, p, dst_col, dst_row, dst_w, dst_h);
    }
    FontBitmap fb;
    int end_of_draw_w = min<size_t>(fb.w() - start_bit, dst_w);
    int end_of_draw_h = min<size_t>(fb.h() - src_y, dst_h);
    for (int j = 0; j < end_of_draw_h; j++)
    {
        for (int i = 0; i < end_of_draw_w; i++)
        {
            p.putpoint(fb.at(start_bit+i, j), dst_col, dst_row);
            src_x++;
            dst_col++;
        }
    }
    return end_of_draw_w;
}

Page layout(const vector<TextBitmap>& vtb, Page& p)
{
    vector<TextScript> script;
    for (TextScript line : script)
    {
        putcharacter(line, p);
    }
    return p;
}

int main(int argc, char* argv[])
{
    Script s;
    Parse(cin, s);
    
    vector<TextBitmap> vtb;
    BuildTextBitmap(s, vtb);

    Page p(60, 60);
    cout << layout(vtb, p);


	return 0;
}

