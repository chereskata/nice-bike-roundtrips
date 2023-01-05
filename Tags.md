# Tags used / constructing the Overpass API query
* Taginfo Database keeps records of the most common tags present in
 the OpenStreetMap database.
* Tags have to be actively selected to be put inside the query result of the Overpass API (whitelist)
* some tags have no special category, but are important for the heatmap the routing algorithm will use to determine "good" routes

## Selection criterion of tags used for routing
### key=[highway](https://wiki.openstreetmap.org/wiki/Key:highway) - roads and paths
* not every road is traversable by bike, especially highways are
forbidden for non-motor vehicles <br>
=> do not include `highway=motorway` and `highway=motorway_link` in query <br>
&nbsp;&nbsp;&nbsp;&nbsp; do not include `highway` tags with [access](https://wiki.openstreetmap.org/wiki/Tag:bicycle%3Dno) set as `bicycle=no` 
&nbsp;&nbsp;&nbsp;&nbsp; whole table of access restrictions in Germany [here](https://wiki.openstreetmap.org/wiki/OSM_tags_for_routing/Access_restrictions#Germany)
* steps are not (easily) passable by bike
=> do not include `highway=steps`

=> following ways with the `highway` tag are needed <br>

| key | value | discard if subtag is present |  
| --- | ----- | ---------------------------- |
| highway | trunk | bicycle=no \| <br> (motorroad=yes & cycleway=* not present) |
| highway | trunk_link | bicycle=no \| <br> (motorroad=yes & cycleway=* not present) |
| highway | primary | bicycle=no \| <br> (motorroad=yes & cycleway=* not present) |
| highway | primary_link | bicycle=no \| <br> (motorroad=yes & cycleway=* not present) |
| highway | secondary | bicycle=no \| <br> (motorroad=yes & cycleway=* not present) |
| highway | secondary_link | bicycle=no \| <br> (motorroad=yes & cycleway=* not present) |
| highway | tertiary | bicycle=no \| <br> (motorroad=yes & cycleway=* not present) |
| highway | tertiary_link | bicycle=no \| <br> (motorroad=yes & cycleway=* not present) |
| highway | unclassified | bicycle=no \| <br> (access=private & bicycle!=yes) \| <br> (motorroad=yes & cycleway=* not present) |
| highway | residential | bicycle=no \| <br> (access=private & bicycle!=yes) |
| highway | living_street | bicycle=no \| <br> (access=private & bicycle!=yes) |
| highway | service | bicycle=no \| <br> (access=private & bicycle!=yes) |
| highway | path | bicycle=no \| <br> (access=private & bicycle!=yes) |
| highway | track | bicycle=no \| <br> (access=private & bicycle!=yes) \| tracktype=grade5 |
| highway | bridleway | bicycle=no \| <br> (access=private & bicycle!=yes) |
| highway | cycleway | / |
| highway | footway | bicycle=no |
| highway | pedestrian | bicycle=no |

* special priority for cycleways and bicycle_road=yes
* additionally exclude all highway=* with [smoothness](https://wiki.openstreetmap.org/wiki/Key:smoothness)=bad,very_bad,horrible,very_horrible,impassable
* exclude all highway=* with [surface](https://wiki.openstreetmap.org/wiki/Key:surface)=stepping_stones,gravel,rock,pebblestone,mud,sand,woodcips
* some road elements can also interesting, for example
beautiful historic bridges ([historic](https://wiki.openstreetmap.org/wiki/Historic)) tag.


### tags that positively influence the heatmap
* any [natural](https://wiki.openstreetmap.org/wiki/Key:natural) tag, depending on their general properties <br>
shall add more or less to the heatmap. <br><br>
Some natural objects are better to be seen form away (for a great sight) and some have an immediate influence on the felt route quality that is taken. <br>
For example a huge mountain has only a positive influence in itself, if viewed from far away. Its heat cycle will look more like a concentric circle with the middle flattened out. On the other hand a tree has only immediate impact on the pleasantness of the route. So its heatmap impact will look like a pylon, if the z axis is the heat. <br><br>
Rivers are abstractly covered by `natural=water`.

* some [tourism](https://wiki.openstreetmap.org/wiki/Key:tourism) tags, namely:

| key | value | discard if subtag is present |  
| --- | ----- | ---------------------------- |
| tourism | alpine_hut | / |
| tourism | artwork | / |
| tourism | attraction | / |
| tourism | picnic_site | / |
| tourism | viewpoint | / |

