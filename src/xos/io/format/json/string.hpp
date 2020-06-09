///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: string.hpp
///
/// Author: $author$
///   Date: 4/16/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_FORMAT_JSON_STRING_HPP
#define _XOS_IO_FORMAT_JSON_STRING_HPP

#include "xos/base/to_string.hpp"

namespace xos {
namespace io {
namespace format {
namespace json {

typedef char_string string_extends;
typedef string_extends::implements string_implements;
///////////////////////////////////////////////////////////////////////
///  Class: string
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS string: virtual public string_implements, public string_extends {
public:
    typedef string_implements implements;
    typedef string_extends extends;

    string(const char* chars, size_t length) {
        this->append(chars, length);
    }
    string(const wchar_t* chars, size_t length) {
        this->append(chars, length);
    }
    string(const char* chars) {
        this->append(chars);
    }
    string(const wchar_t* chars) {
        this->append(chars);
    }
    string(const string &copy): extends(copy) {
    }
    string() {
    }
    virtual ~string() {
    }

    virtual string& assign_to(string& to) const {
        to.clear();
        append_to(to);
        return to;
    }
    virtual string& append_to(string& to) const {
        const char_t* chars = 0;
        size_t length = 0;
        if ((chars = this->has_chars(length))) {
            to.append(chars, length);
        }
        return to;
    }
    virtual string& assign_literal_to(string& to) const {
        to.clear();
        append_literal_to(to);
        return to;
    }
    virtual string& append_literal_to(string& to) const {
        const char_t* chars = 0;
        size_t length = 0;
        to.append("\"");
        for (chars = this->has_chars(length); 0 < length; ++chars, --length) {
            char c = (char)(*chars);
            switch (c) {
            case '"':
                to.append("\\", 1);
            default:
                to.append(chars, 1);
                break;
            }
        }
        to.append("\"");
        return to;
    }
}; /// class _EXPORT_CLASS string

} /// namespace json
} /// namespace format
} /// namespace io
} /// namespace xos

#endif /// _XOS_IO_FORMAT_JSON_STRING_HPP 
