
#include <fstream>
#include <string>
#include <iomanip>
#include <codecvt>

enum FType {
  NO_FILE = 0,
  UNKNOWN,
  UTF8 = 2,
  UTF8_BOM,
  UTF16BE,
  UTF16BE_BOM,
  UTF16LE,
  UTF16LE_BOM
};

FType checkFileType(const char* filename)
{
  FType ret(UNKNOWN);
  std::ifstream ifs;
  ifs.open(filename);
  if (ifs.fail()){
    return NO_FILE;
  }
  char desc[10];
  ifs.read(desc,3);
  if (desc[0] == 0xef && desc[1] == 0xbb && desc[2] == 0xbf){
    return UTF8_BOM;
  } else if (desc[0] == 0xfe && desc[1] == 0xff){
    return UTF16BE_BOM;
  }
  return UNKNOWN;
}

void outputFile(const std::u16string& instr, std::ostream& ostr)
{
  for (const auto& ch : instr){
    if (ch < 0x7f){
      ostr << (char)ch;
    } else {
      ostr << "\\u" << std::hex << std::setfill('0') << std::setw(4) << (int)ch;
    }
  }
}

void outOneFile(const char* infile)
{
  FType file_type = checkFileType(infile);
  if (file_type == UTF8_BOM){
    std::ifstream ifs(infile);
    if (ifs.fail()){
      return;
    }
    std::istreambuf_iterator<char> it(ifs);
    std::istreambuf_iterator<char> last;
    std::string str(it, last);
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
    std::u16string str16 = conv.from_bytes(str.substr(3));
    outputFile(str16, std::cout);
    
  } else if (file_type == NO_FILE ){
    std::cerr << "cannot convert." << std::endl;
  } else {
    std::ifstream ifs(infile);
    if (ifs.fail()){
      return;
    }
    std::istreambuf_iterator<char> it(ifs);
    std::istreambuf_iterator<char> last;
    std::string str(it, last);
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
    std::u16string str16 = conv.from_bytes(str);
    outputFile(str16, std::cout);
  }
}


int main(int argc, char* argv[])
{
  if (argc == 1) {
    std::cerr << *argv << " filename" << std::endl;
    return 0;
  }
  for (int i = 1 ; i < argc; ++i) {
    outOneFile(argv[i]);
  }
  return 0;
}
