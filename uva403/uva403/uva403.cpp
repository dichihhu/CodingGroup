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
typedef vector<vector<char>> FontType;
static const FontType C1A{ { 'A' } }, C1B{ { 'B' } }, C1C{ { 'C' } }, C1D{ { 'D' } }, C1E{ { 'E' } }, C1F{ { 'F' } },
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
static const C5Stroke S2D2S1D1{ '*', '*', '.', '.', '*', '.' };
static const C5Stroke D6{ '.', '.', '.', '.', '.', '.' };
static const FontType C5A{ D1S3D2, S1D3S1D1, S5D1, S1D3S1D1, S1D3S1D1 };
static const FontType C5B{ S4D2, S1D3S1D1, S4D2, S1D3S1D1, S4D2 };
static const FontType C5C{ D1S4D1, S1D3S1D1, S1D5, S1D5, D1S4D1 };
static const FontType C5D{ S4D2, S1D3S1D1, S1D3S1D1, S1D3S1D1, S4D2 };
static const FontType C5E{ S5D1, S1D5, S3D3, S1D5, S5D1 };
static const FontType C5F{ S5D1, S1D5, S3D3, S1D5, S1D5 };
static const FontType C5G{ D1S4D1, S1D5, S1D2S2D1, S1D3S1D1, D1S3D2 };
static const FontType C5H{ S1D3S1D1, S1D3S1D1, S5D1, S1D3S1D1, S1D3S1D1 };
static const FontType C5I{ S5D1, D2S1D3, D2S1D3, D2S1D3, S5D1 };
static const FontType C5J{ D2S3D1, D3S1D2, D3S1D2, S1D2S1D2, D1S2D3 };
static const FontType C5K{ S1D3S1D1, S1D2S1D2, S3D3, S1D2S1D2, S1D3S1D1 };
static const FontType C5L{ S1D5, S1D5, S1D5, S1D5, S5D1 };
static const FontType C5M{ S1D3S1D1, S2D1S2D1, S1D1S1D1S1D1, S1D3S1D1, S1D3S1D1 };
static const FontType C5N{ S1D3S1D1, S2D2S1D1, S1D1S1D1S1D1, S1D2S2D1, S1D3S1D1 };
static const FontType C5O{ D1S3D2, S1D3S1D1, S1D3S1D1, S1D3S1D1, D1S3D2 };
static const FontType C5P{ S4D2, S1D3S1D1, S4D2, S1D5, S1D5 };
static const FontType C5Q{ D1S3D2, S1D3S1D1, S1D3S1D1, S1D2S2D1, D1S4D1 };
static const FontType C5R{ S4D2, S1D3S1D1, S4D2, S1D2S1D2, S1D3S1D1 };
static const FontType C5S{ D1S4D1, S1D5, D1S3D2, D4S1D1, S4D2 };
static const FontType C5T{ S5D1, S1D1S1D1S1D1, D2S1D3, D2S1D3, D1S3D2 };
static const FontType C5U{ S1D3S1D1, S1D3S1D1, S1D3S1D1, S1D3S1D1, D1S3D2 };
static const FontType C5V{ S1D3S1D1, S1D3S1D1, D1S1D1S1D2, D1S1D1S1D2, D2S1D3 };
static const FontType C5W{ S1D3S1D1, S1D3S1D1, S1D1S1D1S1D1, S2D1S2D1, S1D3S1D1 };
static const FontType C5X{ S1D3S1D1, D1S1D1S1D2, D2S1D3, D1S1D1S1D2, S1D3S1D1 };
static const FontType C5Y{ S1D3S1D1, D1S1D1S1D2, D2S1D3, D2S1D3, D2S1D3 };
static const FontType C5Z{ S5D1, D3S1D2, D2S1D3, D1S1D4, S5D1 };
static const FontType C5BLANK{ D6, D6, D6, D6, D6 };

static const map<char, FontType> MC1({ { 'A', C1A }, { 'B', C1B }, { 'C', C1C }, { 'D', C1D }, { 'E', C1E }, { 'F', C1F }
    , { 'G', C1G }, { 'H', C1H }, { 'I', C1I }, { 'J', C1J }, { 'K', C1K }, { 'L', C1L }, { 'M', C1M }
    , { 'N', C1N }, { 'O', C1O }, { 'P', C1P }, { 'Q', C1Q }, { 'R', C1R }, { 'S', C1S }, { 'T', C1T }
    , { 'U', C1U }, { 'V', C1V }, { 'W', C1W }, { 'X', C1X }, { 'Y', C1Y }, { 'Z', C1Z }, { ' ', C1BLANK } });
static const map<char, FontType> MC5({ { 'A', C5A }, { 'B', C5B }, { 'C', C5C }, { 'D', C5D }, { 'E', C5E }, { 'F', C5F }
    , { 'G', C5G }, { 'H', C5H }, { 'I', C5I }, { 'J', C5J }, { 'K', C5K }, { 'L', C5L }, { 'M', C5M }
    , { 'N', C5N }, { 'O', C5O }, { 'P', C5P }, { 'Q', C5Q }, { 'R', C5R }, { 'S', C5S }, { 'T', C5T }
    , { 'U', C5U }, { 'V', C5V }, { 'W', C5W }, { 'X', C5X }, { 'Y', C5Y }, { 'Z', C5Z }, { ' ', C5BLANK } });

class FontData
{
public:
    FontData(FontName f, map<char, FontType> d) : _name(f), _data(d)
    {
        _w = _data['A'][0].size();
        _h = _data['A'].size();
    };
    size_t w() const { return _w; }
    size_t h() const { return _h; }
    const FontType& data(const char c) const {return _data.at(c);}
private:
    FontName _name;
    map<char, FontType> _data;
    size_t _w;
    size_t _h;
};

static const FontData FD1 = FontData(C1, MC1);
static const FontData FD5 = FontData(C5, MC5);
const FontData* GetFontData(const FontName name)
{
    if (name == C1) return &FD1;
    else /*if (name == C5)*/ return &FD5;
}

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
    TextScript(string str) : _op(NOP), _font(NA), _row(0), _col(0), _text(""), _w(0), _h(0)
    {
        istringstream ss(str);
        string tmp("");
        ss >> tmp; set_op(tmp);
        ss >> tmp; set_font(tmp);
        ss >> _row; if (_row) _row--; //bitmap coordinator start from 0
        if (opcode() == P)
        {
            ss >> _col;
            if (_col) _col--; //bitmap coordinator start from 0
        }
        size_t p = str.find_first_of("|");
        if (p != string::npos) _text = str.substr(p+1);
        if (!_text.empty())
        {
            p = _text.find_last_of("|");
            if (p!= string::npos) _text.erase(p, 1);
        }
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
        if (fontname() != NA)
        {
            _w = GetFontData(fontname())->w() * size();
        }
    }
    void set_h() 
    {
        if (fontname() != NA)
        {
            _h = GetFontData(fontname())->h();
        }
    }
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
    Bitmap(FontType ft) : _data(ft)
    {
        _w = ft[0].size();
        _h = ft.size();
    }
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

class Page : public Bitmap
{
public:
    Page(size_t w, size_t h) : Bitmap(w, h) {}
    void putpoint(const char& c, size_t col, size_t row)
    {
        if (col >= w() || row >= h()) return;
        if (c != '.') at(col, row) = c;
    }
    void putchar(const char& c, size_t col, size_t row)
    {
        if (col >= w() || row >= h()) return;
        if (c != ' ') at(col, row) = c;
    }
};

bool Parse(string str, vector<TextScript>& v)
{
    TextScript ts(str);
    v.push_back(ts);
    if (ts.opcode() == EOP) return true;
    else return false;
}

// ------     ............
// |    |     ............
// ------     ............
//            ............

size_t PutFont(const Bitmap& fb, size_t x, size_t y, Page& p, size_t col, size_t row)
{
    size_t i = 0;
    size_t c = col;
    for (i = x; i < fb.w(); i++, c++)
    {
        for (size_t j = y, r = row; j < fb.h(); j++, r++)
        {
            p.putpoint(fb.at(i, j), c, r);
        }
    }
    return (i - x);
}
size_t PutFont(const char& ch, Page& p, size_t col, size_t row)
{
    p.putchar(ch, col, row);
    return 1;
}

void PutTextScript(const TextScript& s, Page& p)
{
    size_t dst_col = 0;
    size_t dst_row = 0;
    size_t src_x = 0;
    size_t src_y = 0;
    switch (s.opcode())
    {
    case EOP:
        return;
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
        dst_col = p.w() > s.w() ? (p.w() - s.w()) : 0;
        dst_row = s.row();
        src_x = p.w() > s.w() ? 0 : (s.w() - p.w());
        src_y = 0;
        break;
    case C:
        dst_col = p.w() > s.w() ? ((p.w() - s.w() + 1) / 2) : 0; //shift right to fulfill udebug test case requirement
        dst_row = s.row();
        src_x = p.w() > s.w() ? 0 : ((s.w() - p.w()) / 2);
        src_y = 0;
        break;
    }

    const FontData* f = GetFontData(s.fontname());
    size_t start_c = src_x / f->w();
    size_t start_bit = src_x % f->w();

    for (size_t c = start_c; c < s.text().size(); c++)
    {
        size_t step = s.fontname() == C5 ?
            PutFont(Bitmap(f->data(s.text()[c])), start_bit, src_y, p, dst_col, dst_row)
          : PutFont(s.text()[c], p, dst_col, dst_row);

        start_bit = 0; // drawing of the 2nd character bitmap always starts from src_x=0
        dst_col += step;
    }
    return;
}

void Layout(const vector<TextScript>& script, Page& p)
{
    for (TextScript line : script)
    {
        PutTextScript(line, p);
    }
    return;
}

int main(int argc, char* argv[])
{
    vector<TextScript> s;
    string str;
    while (getline(cin, str))
    {
        bool eop = false;
        do {
            eop = Parse(str, s);
            if (eop) break;
        } while (getline(cin, str));
        if (eop == false)
        {
            break; // uDebug test case does not end with .EOP. Drop all lines without .EOP.
        }
        Page p(60, 60);
        Layout(s, p);
        cout << p;
        string end(60, '-');
        cout << endl << end << endl << endl;
        s.clear();
    }

	return 0;
}

