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
///   File: to_node.hpp
///
/// Author: $author$
///   Date: 4/15/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_FORMAT_JSON_LIBJSON_TO_NODE_HPP
#define _XOS_IO_FORMAT_JSON_LIBJSON_TO_NODE_HPP

#include "xos/io/format/json/node.hpp"
#include "xos/io/reader.hpp"
#include "xos/io/logger.hpp"
#include <libjson.h>

namespace xos {
namespace io {
namespace format {
namespace json {
namespace libjson {

///////////////////////////////////////////////////////////////////////
///  Class: to_nodet
///////////////////////////////////////////////////////////////////////
template <class TExtends = json::node, class TImplements = typename TExtends::implements>

class _EXPORT_CLASS to_nodet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef to_nodet derives;

    typedef json::node node_t;
    typedef json::string string_t;
    typedef typename string_t::char_t char_t;
    
    to_nodet(node_t& to, char_reader& from): to_(0), v_(0) {
        this->to(to, from);
    }
    to_nodet(node_t& to, const char_string& from): to_(0), v_(0) {
        this->to(to, from);
    }
    to_nodet(char_reader& from): to_(0), v_(0) {
        this->from(from);
    }
    to_nodet(const char_string& from): to_(0), v_(0) {
        this->from(from);
    }
    to_nodet(const to_nodet &copy): extends(copy), to_(0), v_(0) {
    }
    to_nodet(): to_(0), v_(0) {
    }
    virtual ~to_nodet() {
    }

    virtual node_t& from(char_reader& from) {
        return this->to(*this, from);
    }
    virtual node_t& from(const char_string& from) {
        return this->to(*this, from);
    }

    virtual node_t& to(node_t& to, char_reader& from) {
        char c = 0; 
        char_string s;
        while (0 < from.read(&c, 1)) {
            s.append(&c, 1);
        }
        return this->to(to, s);
    }
    virtual node_t& to(node_t& to,const char_string& from) {
        v_ = &to;
        to_ = &derives::to_value;
        this->to(from);
        to_ = 0;
        v_ = 0;
        return to;
    }
protected:
    virtual void to(const char_string& from) {
        const char* json = 0;
        if ((json = from.chars()) && (0 < from.length())) {
            JSONNODE* node = 0;
            if ((node = json_parse(json))) {
                to_value(node);
            }
        }
    }
    typedef void (derives::*to_t)(JSONNODE* node);
    virtual void to(JSONNODE* node) {
        JSONNODE_ITERATOR begin = json_begin(node), end = json_end(node);
        for (JSONNODE_ITERATOR i = begin; i != end; ++i) {
            if ((this->to_)) {
                (this->*to_)(*i);
            }
        }
    }
    virtual void to_value(JSONNODE* node) {
        char type = json_type(node);
        switch (type) {
        case JSON_NODE:
            LOG_DEBUG("JSON_NODE...");
            {
                to_t oldTo = to_;
                to_ = &derives::to_struct;
                v_->clear_object();
                to(node);
                to_ = oldTo;
            }
            LOG_DEBUG("...JSON_NODE");
            break;
        case JSON_ARRAY:
            LOG_DEBUG("JSON_ARRAY...");
            {
                to_t oldTo = to_;
                to_ = &derives::to_array;
                v_->clear_array();
                to(node);
                to_ = oldTo;
            }
            LOG_DEBUG("...JSON_ARRAY");
            break;
        case JSON_STRING:
        case JSON_NUMBER:
        case JSON_BOOL:
        case JSON_NULL:
            switch (type) {
            case JSON_STRING:
                {
                    json_char *value = 0;
                    if ((value = json_as_string(node))) {
                        LOG_DEBUG("...JSON_STRING value = \"" << value << "\"");
                        v_->put(string(value));
                        json_free(value);
                    }
                }
                break;
            case JSON_NUMBER:
                {
                    double value = json_as_float(node);
                    LOG_DEBUG("...JSON_NUMBER = " << double_to_string(value));
                    v_->put(value);
                }
                break;
            case JSON_BOOL:
                {
                    bool value = json_as_bool(node);
                    LOG_DEBUG("...JSON_BOOL = " << bool_to_string(value));
                    v_->put(value);
                }
                break;
            case JSON_NULL:
                LOG_DEBUG("...JSON_NULL");
                v_->put(null_node, json::node::name_null());
                break;
            }
            break;
        default:
            LOG_ERROR("...invalid node type" << type);
        }
    }
    virtual void to_struct(JSONNODE* node) {
        char type = json_type(node);
        switch (type) {
        case JSON_NODE:
            LOG_DEBUG("JSON_NODE...");
            {
                json_char *name = 0;
                if ((name = json_name(node))) {
                    node_t* oldV = v_;
                    node_t v(json::object_node);
                    LOG_DEBUG("...name = \"" << name << "\"");
                    json_free(name);
                    v_ = &v;
                    to(node);
                    v_ = oldV;
                    if ((name = json_name(node))) {
                        v_->put(name, v);
                        json_free(name);
                    }
                }
            }
            LOG_DEBUG("...JSON_NODE");
            break;
        case JSON_ARRAY:
            LOG_DEBUG("JSON_ARRAY...");
            {
                json_char *name = 0;
                if ((name = json_name(node))) {
                    to_t oldTo = to_;
                    node_t* oldV = v_;
                    node_t v(json::array_node);
                    LOG_DEBUG("...name = \"" << name << "\"");
                    json_free(name);
                    v_ = &v;
                    to_ = &derives::to_array;
                    to(node);
                    to_ = oldTo;
                    v_ = oldV;
                    if ((name = json_name(node))) {
                        v_->put(name, v);
                        json_free(name);
                    }
                }
            }
            LOG_DEBUG("...JSON_ARRAY");
            break;
        case JSON_STRING:
        case JSON_NUMBER:
        case JSON_BOOL:
        case JSON_NULL:
            {
                json_char *name = 0;
                if ((name = json_name(node))) {
                    LOG_DEBUG("...name = \"" << name << "\"");
                    switch (type) {
                    case JSON_STRING:
                        {
                            json_char *value = 0;
                            if ((value = json_as_string(node))) {
                                LOG_DEBUG("...JSON_STRING value = \"" << value << "\"");
                                v_->put(name, string_t(value));
                                json_free(value);
                            }
                        }
                        break;
                    case JSON_NUMBER:
                        {
                            double value = json_as_float(node);
                            LOG_DEBUG("...JSON_NUMBER value = " << double_to_string(value));
                            v_->put(name, value);
                        }
                        break;
                    case JSON_BOOL:
                        {
                            bool value = (json_as_bool(node))?(true):(false);
                            LOG_DEBUG("...JSON_BOOL value = " << bool_to_string(value));
                            v_->put(name, value);
                        }
                        break;
                    case JSON_NULL:
                        LOG_DEBUG("...JSON_NULL");
                        v_->put(name, null_node, json::node::name_null());
                        break;
                    }
                    json_free(name);
                }
            }
            break;
        default:
            LOG_ERROR("...invalid node type" << type);
        }
    }
    virtual void to_array(JSONNODE* node) {
        char type = json_type(node);
        switch (type) {
        case JSON_NODE:
            LOG_DEBUG("JSON_NODE...");
            {
                to_t oldTo = to_;
                node_t* oldV = v_;
                node_t v(json::object_node);
                v_ = &v;
                to_ = &derives::to_struct;
                to(node);
                to_ = oldTo;
                v_ = oldV;
                v_->put(v);
            }
            LOG_DEBUG("...JSON_NODE");
            break;
        case JSON_ARRAY:
            LOG_DEBUG("JSON_ARRAY...");
            {
                node_t* oldV = v_;
                node_t v(json::array_node);
                v_ = &v;
                to(node);
                v_ = oldV;
                v_->put(v);
            }
            LOG_DEBUG("...JSON_ARRAY");
            break;
        case JSON_STRING:
        case JSON_NUMBER:
        case JSON_BOOL:
        case JSON_NULL:
            to_value(node);
            break;
        default:
            LOG_ERROR("...invalid node type" << type);
        }
    }

protected:
    to_t to_;
    node_t* v_;
}; /// class _EXPORT_CLASS to_nodet

typedef to_nodet<> to_node;

} /// namespace libjson
} /// namespace json
} /// namespace format
} /// namespace io
} /// namespace xos

#endif /// _XOS_IO_FORMAT_JSON_LIBJSON_TO_NODE_HPP 
