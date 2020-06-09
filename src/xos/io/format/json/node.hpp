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
///   File: node.hpp
///
/// Author: $author$
///   Date: 4/13/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_FORMAT_JSON_NODE_HPP
#define _XOS_IO_FORMAT_JSON_NODE_HPP

#include "xos/io/format/json/string.hpp"
#include "xos/io/reader.hpp"
#include <sstream>
#include <list>

namespace xos {
namespace io {
namespace format {
namespace json {

typedef double number;
typedef bool boolean;

///////////////////////////////////////////////////////////////////////
///  Enum: node_type
///////////////////////////////////////////////////////////////////////
enum node_type {
    unknown_node = 0,
    
    object_node,
    array_node,
    named_node,
    string_node,
    number_node,
    boolean_node,
    null_node,

    first_node_type = object_node,
    last_node_type = null_node,
    node_types = last_node_type - first_node_type + 1
}; /// enum node_type

class _EXPORT_CLASS node;
typedef ::std::list<node> node_list;
typedef base node_extends;
typedef node_extends::implements node_implements;
///////////////////////////////////////////////////////////////////////
///  Class: node
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS node: virtual public node_implements, public node_extends {
public:
    typedef node_implements implements;
    typedef node_extends extends;

    node(const string& name, const node_type& type, const string& value) {
        assign(name, type, value);
    }
    node(const string& name, const char* value) {
        assign(name, value);
    }
    node(const string& name, const wchar_t* value) {
        assign(name, value);
    }
    node(const string& name, const string& value) {
        assign(name, value);
    }
    node(const string& name, const int& value) {
        assign(name, value);
    }
    node(const string& name, const float& value) {
        assign(name, value);
    }
    node(const string& name, const double& value) {
        assign(name, value);
    }
    node(const string& name, const bool& value) {
        assign(name, value);
    }
    node(const string& name, const node& value) {
        assign(name, value);
    }
    node(const char* value) {
        this->operator = (value);
    }
    node(const wchar_t* value) {
        this->operator = (value);
    }
    node(const string& value) {
        this->operator = (value);
    }
    node(const int& value) {
        this->operator = (value);
    }
    node(const float& value) {
        this->operator = (value);
    }
    node(const double& value) {
        this->operator = (value);
    }
    node(const bool& value) {
        this->operator = (value);
    }
    node(const node &copy)
    : type_(copy.type_), string_(copy.string_), number_(copy.number_), 
      boolean_(copy.boolean_), values_(copy.values_) {
    }
    node(const node_type& type, const node_list& value)
    : type_(type), number_(0), boolean_(false), values_(value) {
    }
    node(const node_type& type, const string& name)
    : type_(type), string_(name), number_(0), boolean_(false) {
    }
    node(const node_type& type)
    : type_(type), number_(0), boolean_(false) {
    }
    node()
    : type_(null_node), string_(name_null()), number_(0), boolean_(false) {
    }
    virtual ~node() {
    }

    virtual node& assign(const string& name, const node_type& type, const string& value) {
        clear();
        type_ = named_node;
        string_ = name;
        values_.push_back(node(type, value));
        return *this;
    }
    virtual node& assign(const string& name, const char* value) {
        clear();
        type_ = named_node;
        string_ = name;
        values_.push_back(node(value));
        return *this;
    }
    virtual node& assign(const string& name, const wchar_t* value) {
        clear();
        type_ = named_node;
        string_ = name;
        values_.push_back(node(value));
        return *this;
    }
    virtual node& assign(const string& name, const string& value) {
        clear();
        type_ = named_node;
        string_ = name;
        values_.push_back(node(value));
        return *this;
    }
    virtual node& assign(const string& name, const int& value) {
        clear();
        type_ = named_node;
        string_ = name;
        values_.push_back(node(value));
        return *this;
    }
    virtual node& assign(const string& name, const float& value) {
        clear();
        type_ = named_node;
        string_ = name;
        values_.push_back(node(value));
        return *this;
    }
    virtual node& assign(const string& name, const double& value) {
        clear();
        type_ = named_node;
        string_ = name;
        values_.push_back(node(value));
        return *this;
    }
    virtual node& assign(const string& name, const bool& value) {
        clear();
        type_ = named_node;
        string_ = name;
        values_.push_back(node(value));
        return *this;
    }
    virtual node& assign(const string& name, const node& value) {
        clear();
        type_ = named_node;
        string_ = name;
        if ((value.values().size())) {
            values_.push_back(node(value.type(), value.values()));
        } else {
            values_.push_back(node(value.name()));
        }
        return *this;
    }

    virtual node& clear_named(const string& name) {
        clear();
        type_ = named_node;
        string_ = name;
        return *this;
    }
    virtual node& clear_object() {
        clear();
        type_ = object_node;
        return *this;
    }
    virtual node& clear_array() {
        clear();
        type_ = array_node;
        return *this;
    }
    virtual node& clear() {
        type_ = null_node;
        string_.clear();
        number_ = 0;
        boolean_ = false;
        values_.clear();
        return *this;
    }

    virtual node& put(const string& name, const char* value) {
        string sValue(value);
        values_.push_back(node(name, sValue));
        return *this;
    }
    virtual node& put(const string& name, const wchar_t* value) {
        string sValue(value);
        values_.push_back(node(name, sValue));
        return *this;
    }
    virtual node& put(const string& name, const string& value) {
        values_.push_back(node(name, value));
        return *this;
    }
    virtual node& put(const string& name, const int& value) {
        values_.push_back(node(name, value));
        return *this;
    }
    virtual node& put(const string& name, const float& value) {
        values_.push_back(node(name, value));
        return *this;
    }
    virtual node& put(const string& name, const double& value) {
        values_.push_back(node(name, value));
        return *this;
    }
    virtual node& put(const string& name, const bool& value) {
        values_.push_back(node(name, value));
        return *this;
    }
    virtual node& put(const string& name, const node& value) {
        values_.push_back(node(name, value));
        return *this;
    }

    virtual int& get(int& value, const string& name) const {
        const node* v = 0;
        if ((v = find(name))) {
            node_list::const_iterator begin = v->values_.begin(), end = v->values_.end();
            if (begin != end) {
                if (!(begin->values_.size())) {
                    char_string s(begin->string_.chars());
                    ::std::stringstream ss(s);
                    ss >> value;
                }
            }
        }
        return value;
    }
    virtual float& get(float& value, const string& name) const {
        const node* v = 0;
        if ((v = find(name))) {
            node_list::const_iterator begin = v->values_.begin(), end = v->values_.end();
            if (begin != end) {
                if (!(begin->values_.size())) {
                    char_string s(begin->string_.chars());
                    ::std::stringstream ss(s);
                    ss >> value;
                }
            }
        }
        return value;
    }
    virtual double& get(double& value, const string& name) const {
        const node* v = 0;
        if ((v = find(name))) {
            node_list::const_iterator begin = v->values_.begin(), end = v->values_.end();
            if (begin != end) {
                if (!(begin->values_.size())) {
                    char_string s(begin->string_.chars());
                    ::std::stringstream ss(s);
                    ss >> value;
                }
            }
        }
        return value;
    }
    virtual bool& get(bool& value, const string& name) const {
        const node* v = 0;
        if ((v = find(name))) {
            node_list::const_iterator begin = v->values_.begin(), end = v->values_.end();
            if (begin != end) {
                if (!(begin->values_.size())) {
                    value = !(begin->string_.compare(json::node::name_true()));
                }
            }
        }
        return value;
    }
    virtual string& get(string& value, const string& name) const {
        const node* v = 0;
        if ((v = find(name))) {
            node_list::const_iterator begin = v->values_.begin(), end = v->values_.end();
            if (begin != end) {
                if (!(begin->values_.size())) {
                    value = begin->string_;
                }
            }
        }
        return value;
    }
    virtual node& get(node& value, const string& name) const {
        const node* v = 0;
        if ((v = find(name))) {
            node_list::const_iterator begin = v->values_.begin(), end = v->values_.end();
            if (begin != end) {
                if (!(begin->values_.size())) {
                    value = *begin;
                }
            }
        }
        return value;
    }

    virtual node& put(const string& name, const node_type& type, const char* value) {
        string sValue(value);
        values_.push_back(node(name, type, sValue));
        return *this;
    }
    virtual node& put(const string& name, const node_type& type, const wchar_t* value) {
        string sValue(value);
        values_.push_back(node(name, type, sValue));
        return *this;
    }
    virtual node& put(const string& name, const node_type& type, const string& value) {
        values_.push_back(node(name, type, value));
        return *this;
    }
    virtual node& put(const node_type& type, const char* name) {
        string sName(name);
        values_.push_back(node(type, sName));
        return *this;
    }
    virtual node& put(const node_type& type, const wchar_t* name) {
        string sName(name);
        values_.push_back(node(type, sName));
        return *this;
    }
    virtual node& put(const node_type& type, const string& name) {
        values_.push_back(node(type, name));
        return *this;
    }
    virtual node& put(const char* value) {
        values_.push_back(node(value));
        return *this;
    }
    virtual node& put(const wchar_t* value) {
        values_.push_back(node(value));
        return *this;
    }
    virtual node& put(const string& value) {
        values_.push_back(node(value));
        return *this;
    }
    virtual node& put(const int& value) {
        values_.push_back(node(value));
        return *this;
    }
    virtual node& put(const float& value) {
        values_.push_back(node(value));
        return *this;
    }
    virtual node& put(const double& value) {
        values_.push_back(node(value));
        return *this;
    }
    virtual node& put(const bool& value) {
        values_.push_back(node(value));
        return *this;
    }
    virtual node& put(const node& value) {
        values_.push_back(node(value));
        return *this;
    }

    virtual node& operator = (const char* value) {
        string_ = value;
        number_ = 0;
        boolean_ = false;
        type_ = string_node;
        return *this;
    }
    virtual node& operator = (const wchar_t* value) {
        string_ = value;
        number_ = 0;
        boolean_ = false;
        type_ = string_node;
        return *this;
    }
    virtual node& operator = (const string& value) {
        string_ = value;
        number_ = 0;
        boolean_ = false;
        type_ = string_node;
        return *this;
    }
    virtual node& operator = (const int& value) {
        ::std::stringstream ss;
        ss << value;
        string_ = ss.str().c_str();
        number_ = value;
        boolean_ = false;
        type_ = number_node;
        return *this;
    }
    virtual node& operator = (const float& value) {
        ::std::stringstream ss;
        ss << value;
        string_ = ss.str().c_str();
        number_ = value;
        boolean_ = false;
        type_ = number_node;
        return *this;
    }
    virtual node& operator = (const double& value) {
        ::std::stringstream ss;
        ss << value;
        string_ = ss.str().c_str();
        number_ = value;
        boolean_ = false;
        type_ = number_node;
        return *this;
    }
    virtual node& operator = (const bool& value) {
        string_ = (value)?(name_true()):(name_false());
        number_ = 0;
        boolean_ = value;
        type_ = boolean_node;
        return *this;
    }
    
    static string name_type(const node_type& type) {
        switch (type) {
        case object_node:  return "object";
        case array_node:   return "array";
        case named_node:   return "named";
        case string_node:  return "string";
        case number_node:  return "number";
        case boolean_node: return "boolean";
        case null_node:    return "null";
        }
        return "unknown";
    }
    static string name_true() {
        return "true";
    }
    static string name_false() {
        return "false";
    }
    static string name_null() {
        return "null";
    }
    static const node& value_null() {
        static const node null;
        return null;
    }
    
    virtual string type_name() const {
        return name_type(type_);
    }
    virtual const node_type& type() const {
        return type_;
    }
    virtual const string& name() const {
        return string_;
    }
    virtual const node_list& values() const {
        return values_;
    }
    virtual const node& value() const {
        node_list::const_iterator begin = values_.begin(), end = values_.end();
        if ((begin != end)) {
            return *begin;
        }
        return value_null();
    }
    
    virtual operator string() const {
        return string_;
    }
    virtual operator number() const {
        return number_;
    }
    virtual operator boolean() const {
        return boolean_;
    }

    virtual node& from(char_reader& from) {
        return *this;
    }
    virtual node& from(const char_string& from) {
        return *this;
    }
    virtual string& to(string& to) const;

protected:
    virtual const node* find(const string& name) const {
        node_list::const_iterator begin = values_.begin(), end = values_.end();
        if (begin != end) {
            if (0 < (begin->string_.length())) {
                for (node_list::const_iterator i = begin; i != end; ++i) {
                    const node& n = (*i);
                    if (!(name.compare(n.string_))) {
                        return &n;
                    }
                }
            }
        }
        return 0;
    }
    
protected:
     node_type type_;
     string string_;
     number number_;
     boolean boolean_;
     node_list values_;
}; /// class _EXPORT_CLASS node

} /// namespace json
} /// namespace format
} /// namespace io
} /// namespace xos

#endif /// _XOS_IO_FORMAT_JSON_NODE_HPP 
