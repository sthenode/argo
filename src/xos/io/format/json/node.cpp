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
///   File: node.cpp
///
/// Author: $author$
///   Date: 4/13/2019
///////////////////////////////////////////////////////////////////////
#include "xos/io/format/json/node.hpp"
#include "xos/io/logger.hpp"

namespace xos {
namespace io {
namespace format {
namespace json {

///////////////////////////////////////////////////////////////////////
///  Class: node
///////////////////////////////////////////////////////////////////////
string& node::to(string &to) const {
    if (!(values_.size())) {
        if (named_node > (type_)) {
            XOS_LOG_ERROR("...invalid node type (" << type_ << ") for value");
        } else {
            switch(type_) {
            case number_node:
            case boolean_node:
            case null_node:
                if (0 < (string_.length())) {
                    XOS_LOG_TRACE("...literal " << string_.chars());
                    string_.append_to(to);
                } else {
                }
                break;
            default:
                if (0 < (string_.length())) {
                    XOS_LOG_TRACE("...literal \"" << string_.chars() << "\"");
                    string_.append_literal_to(to);
                } else {
                    to.append("\"");
                    to.append("\"");
                    XOS_LOG_TRACE("literal \"\"");
                }
                break;
            }
        }
    } else {
        node_list::const_iterator b = values_.begin(), e = values_.end(), i;
        if (b != e) {
            const node& v = *b;
            if (!(string_.length())) {
                if ((v.string_.length())) {
                    if ((v.values_.size())) {
                        if (object_node != (type_)) {
                            XOS_LOG_ERROR("invalid node type (" << type_ << ") for object");
                        } else {
                            XOS_LOG_TRACE("object {...");
                            to.append("{");
                            for (i = b; i != e; ++i) {
                                const node& f = *i;
                                if ((i != b)) {
                                    to.append(",");
                                }
                                f.to(to);
                            }
                            to.append("}");
                            XOS_LOG_TRACE("...} object");
                        }
                    } else {
                        v.to(to);
                    }
                } else {
                    if (array_node != (type_)) {
                        XOS_LOG_ERROR("invalid node type (" << type_ << ") for array");
                    } else {
                        XOS_LOG_TRACE("array [...");
                        to.append("[");
                        for (i = b; i != e; ++i) {
                            const node& e = *i;
                            if ((i != b)) {
                                to.append(",");
                            }
                            e.to(to);
                        }
                        to.append("]");
                        XOS_LOG_TRACE("...] array");
                    }
                }
            } else {
                if ((named_node == type_)) {
                    to.append("\"");
                    to.append(string_);
                    to.append("\":");
                    XOS_LOG_TRACE("\"" << string_.chars() << "\":");
                }
                v.to(to);
            }
        }
    }
    return to;
}

} /// namespace json
} /// namespace format
} /// namespace io
} /// namespace xos

