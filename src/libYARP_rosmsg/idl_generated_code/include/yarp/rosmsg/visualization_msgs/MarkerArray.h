/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "visualization_msgs/MarkerArray" msg definition:
//   Marker[] markers
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_visualization_msgs_MarkerArray_h
#define YARP_ROSMSG_visualization_msgs_MarkerArray_h

#include <yarp/os/Wire.h>
#include <yarp/os/Type.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>
#include <yarp/rosmsg/visualization_msgs/Marker.h>

namespace yarp {
namespace rosmsg {
namespace visualization_msgs {

class MarkerArray : public yarp::os::idl::WirePortable
{
public:
    std::vector<yarp::rosmsg::visualization_msgs::Marker> markers;

    MarkerArray() :
            markers()
    {
    }

    void clear()
    {
        // *** markers ***
        markers.clear();
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {
        // *** markers ***
        int len = connection.expectInt32();
        markers.resize(len);
        for (int i=0; i<len; i++) {
            if (!markers[i].read(connection)) {
                return false;
            }
        }

        return !connection.isError();
    }

    bool readBottle(yarp::os::ConnectionReader& connection) override
    {
        connection.convertTextMode();
        yarp::os::idl::WireReader reader(connection);
        if (!reader.readListHeader(1)) {
            return false;
        }

        // *** markers ***
        if (connection.expectInt32() != BOTTLE_TAG_LIST) {
            return false;
        }
        int len = connection.expectInt32();
        markers.resize(len);
        for (int i=0; i<len; i++) {
            if (!markers[i].read(connection)) {
                return false;
            }
        }

        return !connection.isError();
    }

    using yarp::os::idl::WirePortable::read;
    bool read(yarp::os::ConnectionReader& connection) override
    {
        return (connection.isBareMode() ? readBare(connection)
                                        : readBottle(connection));
    }

    bool writeBare(yarp::os::ConnectionWriter& connection) const override
    {
        // *** markers ***
        connection.appendInt32(markers.size());
        for (size_t i=0; i<markers.size(); i++) {
            if (!markers[i].write(connection)) {
                return false;
            }
        }

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) const override
    {
        connection.appendInt32(BOTTLE_TAG_LIST);
        connection.appendInt32(1);

        // *** markers ***
        connection.appendInt32(BOTTLE_TAG_LIST);
        connection.appendInt32(markers.size());
        for (size_t i=0; i<markers.size(); i++) {
            if (!markers[i].write(connection)) {
                return false;
            }
        }

        connection.convertTextMode();
        return !connection.isError();
    }

    using yarp::os::idl::WirePortable::write;
    bool write(yarp::os::ConnectionWriter& connection) const override
    {
        return (connection.isBareMode() ? writeBare(connection)
                                        : writeBottle(connection));
    }

    // This class will serialize ROS style or YARP style depending on protocol.
    // If you need to force a serialization style, use one of these classes:
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::visualization_msgs::MarkerArray> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::visualization_msgs::MarkerArray> bottleStyle;

    // Give source text for class, ROS will need this
    static std::string typeText()
    {
        return std::string("\
Marker[] markers\n\
") + std::string("\n\
================================================================================\n\
MSG: visualization_msgs/Marker\n\
") + yarp::rosmsg::visualization_msgs::Marker::typeText();
    }

    std::string getTypeText() const
    {
        return yarp::rosmsg::visualization_msgs::MarkerArray::typeText();
    }

    // Name the class, ROS will need this
    yarp::os::Type getType() const override
    {
        yarp::os::Type typ = yarp::os::Type::byName("visualization_msgs/MarkerArray", "visualization_msgs/MarkerArray");
        typ.addProperty("md5sum", yarp::os::Value("d155b9ce5188fbaf89745847fd5882d7"));
        typ.addProperty("message_definition", yarp::os::Value(getTypeText()));
        return typ;
    }
};

} // namespace visualization_msgs
} // namespace rosmsg
} // namespace yarp

#endif // YARP_ROSMSG_visualization_msgs_MarkerArray_h
