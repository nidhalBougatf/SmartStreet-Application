import QtQuick 2.0
import QtLocation 5.3
import QtQuick.Controls 2.0

Rectangle{

    width: 800
    height: 600


    Plugin {
        id:somePlugin
        name: "mapbox"
        PluginParameter { name: "mapbox.map_id"; value: "ahmedgu.2begi186" }
        PluginParameter { name: "mapbox.access_token"; value: "pk.eyJ1IjoiYWhtZWRndSIsImEiOiJjaXdrMjhqbTgwMDBjMnptczRhYjR0b2pjIn0.ia9nUgPa7hmbAx4h2T-kmw" }
    }

    Map{
        id: map
        anchors.fill: parent
        plugin: somePlugin
        // property int defaultZoomLevel: 7

            center {
                latitude: 36.899024
                longitude: 10.189739
            }

            zoomLevel: map.maximumZoomLevel

            gesture.enabled: true


            MapCircle {
                    center {
                        latitude: 36.899099
                        longitude: 10.189739
                    }
                    radius: 3.0
                    color: 'green'
                    border.width: 0
                }
}


}
