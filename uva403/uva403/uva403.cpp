// uva403.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

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
//static const C5Stroke D1S4D1{ '.', '*', '*', '*', '*', '.' };
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
    size_t w() const { return _w; }
    size_t h() const { return _h; }
    const FTYPE& data(const char c) {return _data.at(c);}
private:
    FontName _name;
    map<char, FTYPE> _data;
    size_t _w;
    size_t _h;
};

static const map<FontName, FontData> fontmap{ { C1, FontData(C1, MC1) }, { C5, FontData(C5, MC5) } };

const FontData& GetFontData(const FontName name)
{
    return fontmap.at(name);
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

static map<string, Opcode> OPCODE({ { ".P", P }, { ".L", L }, { ".R", R }, { ".C", C }, { ".EOP", EOP } });
static map<string, FontName> FONTNAME({ { "C1", C1 }, { "C5", C5 } });

class TextScript
{
public:
    TextScript() : _op(NOP), _font(NA), _row(0), _col(0), _text(""), _w(0), _h(0)
    {}
    TextScript(istream& in) : _op(NOP), _font(NA), _row(0), _col(0), _text(""), _w(0), _h(0)
    {
        string str("");
        string tmp("");
        getline(in, str, '|');
        istringstream ss(str);
        ss >> tmp; set_op(tmp);
        ss >> tmp; set_font(tmp);
        ss >> _row; _row -= 1; //bitmap coordinator start from 0
        ss >> _col; _col -= 1; //bitmap coordinator start from 0
        getline(in, _text, '|');
        set_w();
        set_h();
    }
    size_t size() const { return _text.size(); }
    const string& text() const { return _text; }
    Opcode opcode() const { return _op; }
    FontName fontname() const { return _font; }
    size_t col() const { return _col; }
    size_t row() const { return _row; }
    size_t w() const { return _w; }
    size_t h() const { return _h; }
private:
    void set_op(string s) { _op = OPCODE[s]; }
    void set_font(string s) { _font = FONTNAME[s]; }
    void set_row(size_t r) { _row = r; }
    void set_col(size_t c) { _col = c; }
    void set_w()
    {
        _w = GetFontData(fontname()).w() * size();
    }
    void set_h() { _h = GetFontData(fontname()).h(); }
    Opcode _op;
    FontName _font;
    size_t _row;
    size_t _col;
    string _text;
    size_t _w;
    size_t _h;
};

class Bitmap
{
public:
    Bitmap(size_t w, size_t h) : 
        _w(w), _h(h), 
        _data(h, vector<char>(w, '.'))
    {}
    size_t w() const { return _w; }
    size_t h() const { return _h; }
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
        at(col, row) = c;
    }
    friend ostream& operator<<(ostream& out, const Bitmap& p)
    {
        for (auto& row : p._data)
        {
            for (auto& c : row)
            {
                out << c;
            }
            out << endl;
        }
        return out;
    }
private:
    size_t _w;
    size_t _h;
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

class Page : public Bitmap
{
public:
    Page(size_t w, size_t h) :
        Bitmap(w, h)
    {}
};

bool Parse(istream& in, vector<TextScript>& v)
{
    string str;
    do {
        TextScript ts(in);
        v.push_back(ts);
    } while (getline(in, str, '\n'));

    return true;
}

// ------     ............
// |    |     ............
// ------     ............
//            ............

size_t PutFontBitmap(const FontBitmap& fb, size_t x, size_t y, Page& p, size_t col, size_t row)
{
    size_t i = 0;
    size_t c = col, r = row;
    for (i = x; i < fb.w(); i++, c++)
    {
        for (size_t j = y; j < fb.h(); j++, r++)
        {
            p.putpoint(fb.at(i, j), c, r);
        }
    }
    return (i - x);
}

void PutTextScript(const TextScript& s, Page& p)
{
    size_t dst_col = 0;
    size_t dst_row = 0;
    size_t src_x = 0;
    size_t src_y = 0;
    switch (s.opcode())
    {
    case P:
        dst_col = s.col();
        dst_row = s.row();
        src_x = 0;
        src_y = 0;
        break;
    case L:
        dst_col = 0;
        dst_row = s.row();
        src_x = 0;
        src_y = 0;
        break;
    case R:
        dst_col = (p.w() - s.w()) > 0 ? (p.w() - s.w()) : 0;
        dst_row = s.row();
        src_x = (p.w() - s.w()) > 0 ? 0 : (s.w() - p.w());
        src_y = 0;
        break;
    case C:
        dst_col = (p.w() - s.w()) > 0 ? ((p.w() - s.w()) / 2) : 0;
        dst_row = s.row();
        src_x = (p.w() - s.w()) > 0 ? 0 : ((s.w() - p.w()) / 2);
        src_y = 0;
        break;
    }

    int dst_w = p.w() - dst_col;
    int dst_h = p.h() - dst_row;

    FontData f = GetFontData(s.fontname());
    size_t start_c = src_x / f.w();
    size_t start_bit = src_x % f.w();

    for (size_t c = start_c; c < s.text().size(); c++)
    {
        size_t step = PutFontBitmap(FontBitmap(f.data(s.text()[c])), start_bit, src_y, p, dst_col, dst_row);
        start_bit += step;
        dst_col += step;
    }
}


void layout(const vector<TextScript>& script, Page& p)
{
    for (TextScript line : script)
    {
        PutTextScript(line, p);
    }
}

int main(int argc, char* argv[])
{
    vector<TextScript> s;
    Parse(cin, s);

    Page p(60, 60);
    layout(s, p);

    cout << p;

	return 0;
}

