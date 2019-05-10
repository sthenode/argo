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
    switch(type_) {

    case number_node:
    case boolean_node:
    case null_node:
        if (0 < (string_.length())) {
            LOG_DEBUG("...literal " << string_.chars());
            string_.append_to(to);
        } else {
            LOG_ERROR("...unexpected empty literal");
        }
        break;

    case string_node:
        if (0 < (string_.length())) {
            LOG_DEBUG("...literal \"" << string_.chars() << "\"");
            string_.append_literal_to(to);
        } else {
            to.append("\"");
            to.append("\"");
            LOG_DEBUG("...literal \"\"");
        }
        break;

    case named_node:
    case array_node:
    case object_node:
        if (0 < (values_.size())) {
            node_list::const_iterator b = values_.begin(), e = values_.end();

            if (named_node != (type_)) {
                LOG_DEBUG(((array_node != (type_))?("object {"):("array [")) << "...");
                to.append((array_node != (type_))?("{"):("["));
                for (node_list::const_iterator i = b; i != e; ++i) {
                    const node& v = *i;
                    if ((i != b)) {
                        to.append(",");
                    }
                    v.to(to);
                }
                to.append((array_node != (type_))?("}"):("]"));
                LOG_DEBUG("..." << ((array_node != (type_))?("} object"):("] array")));
            } else {
                const node& v = *b;
                to.append("\"");
                to.append(string_);
                to.append("\":");
                LOG_DEBUG("...named \"" << string_.chars() << "\":");
                v.to(to);
            }
        } else {
            LOG_ERROR("...unexpected empty values");
        }
        break;

    default:
        LOG_ERROR("...unexpected type = " << type_);
        break;
    }
    return to;
}

} /// namespace json
} /// namespace format
} /// namespace io
} /// namespace xos
