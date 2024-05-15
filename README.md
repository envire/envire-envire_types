- [ ] if the config map does not contain all required keys: throw error. in this case we are not allowed to add item
into the graph. otherwise this item contains empty information

- [ ] add envire registration for serialization

- [ ] motor DC/PID rename config key minValue/maxValue to minPosition/maxPosition

- [ ] sensors CameraSensor/RaySensor rename config key opening_width/opening_height to openingWidget/openingHeight

- [ ] Provide interfaces for methods serialize & getFullConfigMap

- [ ] Const-correctness (e. g. getFullConfigMap)
