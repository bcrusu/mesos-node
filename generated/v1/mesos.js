module.exports = require("protobufjs").newBuilder({})['import']({
    "package": "mesos.v1",
    "options": {
        "java_package": "org.apache.mesos.v1",
        "java_outer_classname": "Protos"
    },
    "messages": [
        {
            "name": "FrameworkID",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "value",
                    "id": 1
                }
            ]
        },
        {
            "name": "OfferID",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "value",
                    "id": 1
                }
            ]
        },
        {
            "name": "AgentID",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "value",
                    "id": 1
                }
            ]
        },
        {
            "name": "TaskID",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "value",
                    "id": 1
                }
            ]
        },
        {
            "name": "ExecutorID",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "value",
                    "id": 1
                }
            ]
        },
        {
            "name": "ContainerID",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "value",
                    "id": 1
                }
            ]
        },
        {
            "name": "TimeInfo",
            "fields": [
                {
                    "rule": "required",
                    "type": "int64",
                    "name": "nanoseconds",
                    "id": 1
                }
            ]
        },
        {
            "name": "DurationInfo",
            "fields": [
                {
                    "rule": "required",
                    "type": "int64",
                    "name": "nanoseconds",
                    "id": 1
                }
            ]
        },
        {
            "name": "Address",
            "fields": [
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "hostname",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "ip",
                    "id": 2
                },
                {
                    "rule": "required",
                    "type": "int32",
                    "name": "port",
                    "id": 3
                }
            ]
        },
        {
            "name": "URL",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "scheme",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "Address",
                    "name": "address",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "path",
                    "id": 3
                },
                {
                    "rule": "repeated",
                    "type": "Parameter",
                    "name": "query",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "fragment",
                    "id": 5
                }
            ]
        },
        {
            "name": "Unavailability",
            "fields": [
                {
                    "rule": "required",
                    "type": "TimeInfo",
                    "name": "start",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "DurationInfo",
                    "name": "duration",
                    "id": 2
                }
            ]
        },
        {
            "name": "MachineID",
            "fields": [
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "hostname",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "ip",
                    "id": 2
                }
            ]
        },
        {
            "name": "MachineInfo",
            "fields": [
                {
                    "rule": "required",
                    "type": "MachineID",
                    "name": "id",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "Mode",
                    "name": "mode",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "Unavailability",
                    "name": "unavailability",
                    "id": 3
                }
            ],
            "enums": [
                {
                    "name": "Mode",
                    "values": [
                        {
                            "name": "UP",
                            "id": 1
                        },
                        {
                            "name": "DRAINING",
                            "id": 2
                        },
                        {
                            "name": "DOWN",
                            "id": 3
                        }
                    ]
                }
            ]
        },
        {
            "name": "FrameworkInfo",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "user",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "string",
                    "name": "name",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "FrameworkID",
                    "name": "id",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "failover_timeout",
                    "id": 4,
                    "options": {
                        "default": 0
                    }
                },
                {
                    "rule": "optional",
                    "type": "bool",
                    "name": "checkpoint",
                    "id": 5,
                    "options": {
                        "default": false
                    }
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "role",
                    "id": 6,
                    "options": {
                        "default": "*"
                    }
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "hostname",
                    "id": 7
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "principal",
                    "id": 8
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "webui_url",
                    "id": 9
                },
                {
                    "rule": "repeated",
                    "type": "Capability",
                    "name": "capabilities",
                    "id": 10
                },
                {
                    "rule": "optional",
                    "type": "Labels",
                    "name": "labels",
                    "id": 11
                }
            ],
            "messages": [
                {
                    "name": "Capability",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "Type",
                            "name": "type",
                            "id": 1
                        }
                    ],
                    "enums": [
                        {
                            "name": "Type",
                            "values": [
                                {
                                    "name": "REVOCABLE_RESOURCES",
                                    "id": 1
                                }
                            ]
                        }
                    ]
                }
            ]
        },
        {
            "name": "HealthCheck",
            "fields": [
                {
                    "rule": "optional",
                    "type": "HTTP",
                    "name": "http",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "delay_seconds",
                    "id": 2,
                    "options": {
                        "default": 15
                    }
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "interval_seconds",
                    "id": 3,
                    "options": {
                        "default": 10
                    }
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "timeout_seconds",
                    "id": 4,
                    "options": {
                        "default": 20
                    }
                },
                {
                    "rule": "optional",
                    "type": "uint32",
                    "name": "consecutive_failures",
                    "id": 5,
                    "options": {
                        "default": 3
                    }
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "grace_period_seconds",
                    "id": 6,
                    "options": {
                        "default": 10
                    }
                },
                {
                    "rule": "optional",
                    "type": "CommandInfo",
                    "name": "command",
                    "id": 7
                }
            ],
            "messages": [
                {
                    "name": "HTTP",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "uint32",
                            "name": "port",
                            "id": 1
                        },
                        {
                            "rule": "optional",
                            "type": "string",
                            "name": "path",
                            "id": 2,
                            "options": {
                                "default": "/"
                            }
                        },
                        {
                            "rule": "repeated",
                            "type": "uint32",
                            "name": "statuses",
                            "id": 4
                        }
                    ]
                }
            ]
        },
        {
            "name": "CommandInfo",
            "fields": [
                {
                    "rule": "optional",
                    "type": "ContainerInfo",
                    "name": "container",
                    "id": 4
                },
                {
                    "rule": "repeated",
                    "type": "URI",
                    "name": "uris",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "Environment",
                    "name": "environment",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "bool",
                    "name": "shell",
                    "id": 6,
                    "options": {
                        "default": true
                    }
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "value",
                    "id": 3
                },
                {
                    "rule": "repeated",
                    "type": "string",
                    "name": "arguments",
                    "id": 7
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "user",
                    "id": 5
                }
            ],
            "messages": [
                {
                    "name": "URI",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "string",
                            "name": "value",
                            "id": 1
                        },
                        {
                            "rule": "optional",
                            "type": "bool",
                            "name": "executable",
                            "id": 2
                        },
                        {
                            "rule": "optional",
                            "type": "bool",
                            "name": "extract",
                            "id": 3,
                            "options": {
                                "default": true
                            }
                        },
                        {
                            "rule": "optional",
                            "type": "bool",
                            "name": "cache",
                            "id": 4
                        }
                    ]
                },
                {
                    "name": "ContainerInfo",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "string",
                            "name": "image",
                            "id": 1
                        },
                        {
                            "rule": "repeated",
                            "type": "string",
                            "name": "options",
                            "id": 2
                        }
                    ]
                }
            ]
        },
        {
            "name": "ExecutorInfo",
            "fields": [
                {
                    "rule": "required",
                    "type": "ExecutorID",
                    "name": "executor_id",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "FrameworkID",
                    "name": "framework_id",
                    "id": 8
                },
                {
                    "rule": "required",
                    "type": "CommandInfo",
                    "name": "command",
                    "id": 7
                },
                {
                    "rule": "optional",
                    "type": "ContainerInfo",
                    "name": "container",
                    "id": 11
                },
                {
                    "rule": "repeated",
                    "type": "Resource",
                    "name": "resources",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "name",
                    "id": 9
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "source",
                    "id": 10
                },
                {
                    "rule": "optional",
                    "type": "bytes",
                    "name": "data",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "DiscoveryInfo",
                    "name": "discovery",
                    "id": 12
                }
            ]
        },
        {
            "name": "MasterInfo",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "id",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "uint32",
                    "name": "ip",
                    "id": 2
                },
                {
                    "rule": "required",
                    "type": "uint32",
                    "name": "port",
                    "id": 3,
                    "options": {
                        "default": 5050
                    }
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "pid",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "hostname",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "version",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "Address",
                    "name": "address",
                    "id": 7
                }
            ]
        },
        {
            "name": "AgentInfo",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "hostname",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "int32",
                    "name": "port",
                    "id": 8,
                    "options": {
                        "default": 5051
                    }
                },
                {
                    "rule": "repeated",
                    "type": "Resource",
                    "name": "resources",
                    "id": 3
                },
                {
                    "rule": "repeated",
                    "type": "Attribute",
                    "name": "attributes",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "AgentID",
                    "name": "id",
                    "id": 6
                }
            ]
        },
        {
            "name": "Value",
            "fields": [
                {
                    "rule": "required",
                    "type": "Type",
                    "name": "type",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "Scalar",
                    "name": "scalar",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "Ranges",
                    "name": "ranges",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "Set",
                    "name": "set",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "Text",
                    "name": "text",
                    "id": 5
                }
            ],
            "messages": [
                {
                    "name": "Scalar",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "double",
                            "name": "value",
                            "id": 1
                        }
                    ]
                },
                {
                    "name": "Range",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "uint64",
                            "name": "begin",
                            "id": 1
                        },
                        {
                            "rule": "required",
                            "type": "uint64",
                            "name": "end",
                            "id": 2
                        }
                    ]
                },
                {
                    "name": "Ranges",
                    "fields": [
                        {
                            "rule": "repeated",
                            "type": "Range",
                            "name": "range",
                            "id": 1
                        }
                    ]
                },
                {
                    "name": "Set",
                    "fields": [
                        {
                            "rule": "repeated",
                            "type": "string",
                            "name": "item",
                            "id": 1
                        }
                    ]
                },
                {
                    "name": "Text",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "string",
                            "name": "value",
                            "id": 1
                        }
                    ]
                }
            ],
            "enums": [
                {
                    "name": "Type",
                    "values": [
                        {
                            "name": "SCALAR",
                            "id": 0
                        },
                        {
                            "name": "RANGES",
                            "id": 1
                        },
                        {
                            "name": "SET",
                            "id": 2
                        },
                        {
                            "name": "TEXT",
                            "id": 3
                        }
                    ]
                }
            ]
        },
        {
            "name": "Attribute",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "name",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "Value.Type",
                    "name": "type",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "Value.Scalar",
                    "name": "scalar",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "Value.Ranges",
                    "name": "ranges",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "Value.Set",
                    "name": "set",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "Value.Text",
                    "name": "text",
                    "id": 5
                }
            ]
        },
        {
            "name": "Resource",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "name",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "Value.Type",
                    "name": "type",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "Value.Scalar",
                    "name": "scalar",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "Value.Ranges",
                    "name": "ranges",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "Value.Set",
                    "name": "set",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "role",
                    "id": 6,
                    "options": {
                        "default": "*"
                    }
                },
                {
                    "rule": "optional",
                    "type": "ReservationInfo",
                    "name": "reservation",
                    "id": 8
                },
                {
                    "rule": "optional",
                    "type": "DiskInfo",
                    "name": "disk",
                    "id": 7
                },
                {
                    "rule": "optional",
                    "type": "RevocableInfo",
                    "name": "revocable",
                    "id": 9
                }
            ],
            "messages": [
                {
                    "name": "ReservationInfo",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "string",
                            "name": "principal",
                            "id": 1
                        }
                    ]
                },
                {
                    "name": "DiskInfo",
                    "fields": [
                        {
                            "rule": "optional",
                            "type": "Persistence",
                            "name": "persistence",
                            "id": 1
                        },
                        {
                            "rule": "optional",
                            "type": "Volume",
                            "name": "volume",
                            "id": 2
                        }
                    ],
                    "messages": [
                        {
                            "name": "Persistence",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "string",
                                    "name": "id",
                                    "id": 1
                                }
                            ]
                        }
                    ]
                },
                {
                    "name": "RevocableInfo",
                    "fields": []
                }
            ]
        },
        {
            "name": "TrafficControlStatistics",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "id",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "backlog",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "bytes",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "drops",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "overlimits",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "packets",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "qlen",
                    "id": 7
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "ratebps",
                    "id": 8
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "ratepps",
                    "id": 9
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "requeues",
                    "id": 10
                }
            ]
        },
        {
            "name": "ResourceStatistics",
            "fields": [
                {
                    "rule": "required",
                    "type": "double",
                    "name": "timestamp",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "uint32",
                    "name": "processes",
                    "id": 30
                },
                {
                    "rule": "optional",
                    "type": "uint32",
                    "name": "threads",
                    "id": 31
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "cpus_user_time_secs",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "cpus_system_time_secs",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "cpus_limit",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "uint32",
                    "name": "cpus_nr_periods",
                    "id": 7
                },
                {
                    "rule": "optional",
                    "type": "uint32",
                    "name": "cpus_nr_throttled",
                    "id": 8
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "cpus_throttled_time_secs",
                    "id": 9
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_total_bytes",
                    "id": 36
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_total_memsw_bytes",
                    "id": 37
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_limit_bytes",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_soft_limit_bytes",
                    "id": 38
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_file_bytes",
                    "id": 10
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_anon_bytes",
                    "id": 11
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_cache_bytes",
                    "id": 39
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_rss_bytes",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_mapped_file_bytes",
                    "id": 12
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_swap_bytes",
                    "id": 40
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_low_pressure_counter",
                    "id": 32
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_medium_pressure_counter",
                    "id": 33
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "mem_critical_pressure_counter",
                    "id": 34
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "disk_limit_bytes",
                    "id": 26
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "disk_used_bytes",
                    "id": 27
                },
                {
                    "rule": "optional",
                    "type": "PerfStatistics",
                    "name": "perf",
                    "id": 13
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "net_rx_packets",
                    "id": 14
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "net_rx_bytes",
                    "id": 15
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "net_rx_errors",
                    "id": 16
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "net_rx_dropped",
                    "id": 17
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "net_tx_packets",
                    "id": 18
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "net_tx_bytes",
                    "id": 19
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "net_tx_errors",
                    "id": 20
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "net_tx_dropped",
                    "id": 21
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "net_tcp_rtt_microsecs_p50",
                    "id": 22
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "net_tcp_rtt_microsecs_p90",
                    "id": 23
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "net_tcp_rtt_microsecs_p95",
                    "id": 24
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "net_tcp_rtt_microsecs_p99",
                    "id": 25
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "net_tcp_active_connections",
                    "id": 28
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "net_tcp_time_wait_connections",
                    "id": 29
                },
                {
                    "rule": "repeated",
                    "type": "TrafficControlStatistics",
                    "name": "net_traffic_control_statistics",
                    "id": 35
                }
            ]
        },
        {
            "name": "ResourceUsage",
            "fields": [
                {
                    "rule": "repeated",
                    "type": "Executor",
                    "name": "executors",
                    "id": 1
                },
                {
                    "rule": "repeated",
                    "type": "Resource",
                    "name": "total",
                    "id": 2
                }
            ],
            "messages": [
                {
                    "name": "Executor",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "ExecutorInfo",
                            "name": "executor_info",
                            "id": 1
                        },
                        {
                            "rule": "repeated",
                            "type": "Resource",
                            "name": "allocated",
                            "id": 2
                        },
                        {
                            "rule": "optional",
                            "type": "ResourceStatistics",
                            "name": "statistics",
                            "id": 3
                        }
                    ]
                }
            ]
        },
        {
            "name": "PerfStatistics",
            "fields": [
                {
                    "rule": "required",
                    "type": "double",
                    "name": "timestamp",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "double",
                    "name": "duration",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "cycles",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "stalled_cycles_frontend",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "stalled_cycles_backend",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "instructions",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "cache_references",
                    "id": 7
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "cache_misses",
                    "id": 8
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "branches",
                    "id": 9
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "branch_misses",
                    "id": 10
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "bus_cycles",
                    "id": 11
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "ref_cycles",
                    "id": 12
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "cpu_clock",
                    "id": 13
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "task_clock",
                    "id": 14
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "page_faults",
                    "id": 15
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "minor_faults",
                    "id": 16
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "major_faults",
                    "id": 17
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "context_switches",
                    "id": 18
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "cpu_migrations",
                    "id": 19
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "alignment_faults",
                    "id": 20
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "emulation_faults",
                    "id": 21
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "l1_dcache_loads",
                    "id": 22
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "l1_dcache_load_misses",
                    "id": 23
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "l1_dcache_stores",
                    "id": 24
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "l1_dcache_store_misses",
                    "id": 25
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "l1_dcache_prefetches",
                    "id": 26
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "l1_dcache_prefetch_misses",
                    "id": 27
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "l1_icache_loads",
                    "id": 28
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "l1_icache_load_misses",
                    "id": 29
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "l1_icache_prefetches",
                    "id": 30
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "l1_icache_prefetch_misses",
                    "id": 31
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "llc_loads",
                    "id": 32
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "llc_load_misses",
                    "id": 33
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "llc_stores",
                    "id": 34
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "llc_store_misses",
                    "id": 35
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "llc_prefetches",
                    "id": 36
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "llc_prefetch_misses",
                    "id": 37
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "dtlb_loads",
                    "id": 38
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "dtlb_load_misses",
                    "id": 39
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "dtlb_stores",
                    "id": 40
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "dtlb_store_misses",
                    "id": 41
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "dtlb_prefetches",
                    "id": 42
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "dtlb_prefetch_misses",
                    "id": 43
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "itlb_loads",
                    "id": 44
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "itlb_load_misses",
                    "id": 45
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "branch_loads",
                    "id": 46
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "branch_load_misses",
                    "id": 47
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "node_loads",
                    "id": 48
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "node_load_misses",
                    "id": 49
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "node_stores",
                    "id": 50
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "node_store_misses",
                    "id": 51
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "node_prefetches",
                    "id": 52
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "node_prefetch_misses",
                    "id": 53
                }
            ]
        },
        {
            "name": "Request",
            "fields": [
                {
                    "rule": "optional",
                    "type": "AgentID",
                    "name": "agent_id",
                    "id": 1
                },
                {
                    "rule": "repeated",
                    "type": "Resource",
                    "name": "resources",
                    "id": 2
                }
            ]
        },
        {
            "name": "Offer",
            "fields": [
                {
                    "rule": "required",
                    "type": "OfferID",
                    "name": "id",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "FrameworkID",
                    "name": "framework_id",
                    "id": 2
                },
                {
                    "rule": "required",
                    "type": "AgentID",
                    "name": "agent_id",
                    "id": 3
                },
                {
                    "rule": "required",
                    "type": "string",
                    "name": "hostname",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "URL",
                    "name": "url",
                    "id": 8
                },
                {
                    "rule": "repeated",
                    "type": "Resource",
                    "name": "resources",
                    "id": 5
                },
                {
                    "rule": "repeated",
                    "type": "Attribute",
                    "name": "attributes",
                    "id": 7
                },
                {
                    "rule": "repeated",
                    "type": "ExecutorID",
                    "name": "executor_ids",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "Unavailability",
                    "name": "unavailability",
                    "id": 9
                }
            ],
            "messages": [
                {
                    "name": "Operation",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "Type",
                            "name": "type",
                            "id": 1
                        },
                        {
                            "rule": "optional",
                            "type": "Launch",
                            "name": "launch",
                            "id": 2
                        },
                        {
                            "rule": "optional",
                            "type": "Reserve",
                            "name": "reserve",
                            "id": 3
                        },
                        {
                            "rule": "optional",
                            "type": "Unreserve",
                            "name": "unreserve",
                            "id": 4
                        },
                        {
                            "rule": "optional",
                            "type": "Create",
                            "name": "create",
                            "id": 5
                        },
                        {
                            "rule": "optional",
                            "type": "Destroy",
                            "name": "destroy",
                            "id": 6
                        }
                    ],
                    "messages": [
                        {
                            "name": "Launch",
                            "fields": [
                                {
                                    "rule": "repeated",
                                    "type": "TaskInfo",
                                    "name": "task_infos",
                                    "id": 1
                                }
                            ]
                        },
                        {
                            "name": "Reserve",
                            "fields": [
                                {
                                    "rule": "repeated",
                                    "type": "Resource",
                                    "name": "resources",
                                    "id": 1
                                }
                            ]
                        },
                        {
                            "name": "Unreserve",
                            "fields": [
                                {
                                    "rule": "repeated",
                                    "type": "Resource",
                                    "name": "resources",
                                    "id": 1
                                }
                            ]
                        },
                        {
                            "name": "Create",
                            "fields": [
                                {
                                    "rule": "repeated",
                                    "type": "Resource",
                                    "name": "volumes",
                                    "id": 1
                                }
                            ]
                        },
                        {
                            "name": "Destroy",
                            "fields": [
                                {
                                    "rule": "repeated",
                                    "type": "Resource",
                                    "name": "volumes",
                                    "id": 1
                                }
                            ]
                        }
                    ],
                    "enums": [
                        {
                            "name": "Type",
                            "values": [
                                {
                                    "name": "LAUNCH",
                                    "id": 1
                                },
                                {
                                    "name": "RESERVE",
                                    "id": 2
                                },
                                {
                                    "name": "UNRESERVE",
                                    "id": 3
                                },
                                {
                                    "name": "CREATE",
                                    "id": 4
                                },
                                {
                                    "name": "DESTROY",
                                    "id": 5
                                }
                            ]
                        }
                    ]
                }
            ]
        },
        {
            "name": "InverseOffer",
            "fields": [
                {
                    "rule": "required",
                    "type": "OfferID",
                    "name": "id",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "URL",
                    "name": "url",
                    "id": 2
                },
                {
                    "rule": "required",
                    "type": "FrameworkID",
                    "name": "framework_id",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "AgentID",
                    "name": "agent_id",
                    "id": 4
                },
                {
                    "rule": "required",
                    "type": "Unavailability",
                    "name": "unavailability",
                    "id": 5
                },
                {
                    "rule": "repeated",
                    "type": "Resource",
                    "name": "resources",
                    "id": 6
                }
            ]
        },
        {
            "name": "TaskInfo",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "name",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "TaskID",
                    "name": "task_id",
                    "id": 2
                },
                {
                    "rule": "required",
                    "type": "AgentID",
                    "name": "agent_id",
                    "id": 3
                },
                {
                    "rule": "repeated",
                    "type": "Resource",
                    "name": "resources",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "ExecutorInfo",
                    "name": "executor",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "CommandInfo",
                    "name": "command",
                    "id": 7
                },
                {
                    "rule": "optional",
                    "type": "ContainerInfo",
                    "name": "container",
                    "id": 9
                },
                {
                    "rule": "optional",
                    "type": "bytes",
                    "name": "data",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "HealthCheck",
                    "name": "health_check",
                    "id": 8
                },
                {
                    "rule": "optional",
                    "type": "Labels",
                    "name": "labels",
                    "id": 10
                },
                {
                    "rule": "optional",
                    "type": "DiscoveryInfo",
                    "name": "discovery",
                    "id": 11
                }
            ]
        },
        {
            "name": "TaskStatus",
            "fields": [
                {
                    "rule": "required",
                    "type": "TaskID",
                    "name": "task_id",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "TaskState",
                    "name": "state",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "message",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "Source",
                    "name": "source",
                    "id": 9
                },
                {
                    "rule": "optional",
                    "type": "Reason",
                    "name": "reason",
                    "id": 10
                },
                {
                    "rule": "optional",
                    "type": "bytes",
                    "name": "data",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "AgentID",
                    "name": "agent_id",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "ExecutorID",
                    "name": "executor_id",
                    "id": 7
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "timestamp",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "bytes",
                    "name": "uuid",
                    "id": 11
                },
                {
                    "rule": "optional",
                    "type": "bool",
                    "name": "healthy",
                    "id": 8
                },
                {
                    "rule": "optional",
                    "type": "Labels",
                    "name": "labels",
                    "id": 12
                }
            ],
            "enums": [
                {
                    "name": "Source",
                    "values": [
                        {
                            "name": "SOURCE_MASTER",
                            "id": 0
                        },
                        {
                            "name": "SOURCE_AGENT",
                            "id": 1
                        },
                        {
                            "name": "SOURCE_EXECUTOR",
                            "id": 2
                        }
                    ]
                },
                {
                    "name": "Reason",
                    "values": [
                        {
                            "name": "REASON_COMMAND_EXECUTOR_FAILED",
                            "id": 0
                        },
                        {
                            "name": "REASON_CONTAINER_LAUNCH_FAILED",
                            "id": 21
                        },
                        {
                            "name": "REASON_CONTAINER_LIMITATION",
                            "id": 19
                        },
                        {
                            "name": "REASON_CONTAINER_LIMITATION_DISK",
                            "id": 20
                        },
                        {
                            "name": "REASON_CONTAINER_LIMITATION_MEMORY",
                            "id": 8
                        },
                        {
                            "name": "REASON_CONTAINER_PREEMPTED",
                            "id": 17
                        },
                        {
                            "name": "REASON_CONTAINER_UPDATE_FAILED",
                            "id": 22
                        },
                        {
                            "name": "REASON_EXECUTOR_REGISTRATION_TIMEOUT",
                            "id": 23
                        },
                        {
                            "name": "REASON_EXECUTOR_REREGISTRATION_TIMEOUT",
                            "id": 24
                        },
                        {
                            "name": "REASON_EXECUTOR_TERMINATED",
                            "id": 1
                        },
                        {
                            "name": "REASON_EXECUTOR_UNREGISTERED",
                            "id": 2
                        },
                        {
                            "name": "REASON_FRAMEWORK_REMOVED",
                            "id": 3
                        },
                        {
                            "name": "REASON_GC_ERROR",
                            "id": 4
                        },
                        {
                            "name": "REASON_INVALID_FRAMEWORKID",
                            "id": 5
                        },
                        {
                            "name": "REASON_INVALID_OFFERS",
                            "id": 6
                        },
                        {
                            "name": "REASON_MASTER_DISCONNECTED",
                            "id": 7
                        },
                        {
                            "name": "REASON_RECONCILIATION",
                            "id": 9
                        },
                        {
                            "name": "REASON_RESOURCES_UNKNOWN",
                            "id": 18
                        },
                        {
                            "name": "REASON_AGENT_DISCONNECTED",
                            "id": 10
                        },
                        {
                            "name": "REASON_AGENT_REMOVED",
                            "id": 11
                        },
                        {
                            "name": "REASON_AGENT_RESTARTED",
                            "id": 12
                        },
                        {
                            "name": "REASON_AGENT_UNKNOWN",
                            "id": 13
                        },
                        {
                            "name": "REASON_TASK_INVALID",
                            "id": 14
                        },
                        {
                            "name": "REASON_TASK_UNAUTHORIZED",
                            "id": 15
                        },
                        {
                            "name": "REASON_TASK_UNKNOWN",
                            "id": 16
                        }
                    ]
                }
            ]
        },
        {
            "name": "Filters",
            "fields": [
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "refuse_seconds",
                    "id": 1,
                    "options": {
                        "default": 5
                    }
                }
            ]
        },
        {
            "name": "Environment",
            "fields": [
                {
                    "rule": "repeated",
                    "type": "Variable",
                    "name": "variables",
                    "id": 1
                }
            ],
            "messages": [
                {
                    "name": "Variable",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "string",
                            "name": "name",
                            "id": 1
                        },
                        {
                            "rule": "required",
                            "type": "string",
                            "name": "value",
                            "id": 2
                        }
                    ]
                }
            ]
        },
        {
            "name": "Parameter",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "key",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "string",
                    "name": "value",
                    "id": 2
                }
            ]
        },
        {
            "name": "Parameters",
            "fields": [
                {
                    "rule": "repeated",
                    "type": "Parameter",
                    "name": "parameter",
                    "id": 1
                }
            ]
        },
        {
            "name": "Credential",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "principal",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "secret",
                    "id": 2
                }
            ]
        },
        {
            "name": "Credentials",
            "fields": [
                {
                    "rule": "repeated",
                    "type": "Credential",
                    "name": "credentials",
                    "id": 1
                }
            ]
        },
        {
            "name": "RateLimit",
            "fields": [
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "qps",
                    "id": 1
                },
                {
                    "rule": "required",
                    "type": "string",
                    "name": "principal",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "capacity",
                    "id": 3
                }
            ]
        },
        {
            "name": "RateLimits",
            "fields": [
                {
                    "rule": "repeated",
                    "type": "RateLimit",
                    "name": "limits",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "double",
                    "name": "aggregate_default_qps",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "uint64",
                    "name": "aggregate_default_capacity",
                    "id": 3
                }
            ]
        },
        {
            "name": "Image",
            "fields": [
                {
                    "rule": "required",
                    "type": "Type",
                    "name": "type",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "AppC",
                    "name": "appc",
                    "id": 2
                }
            ],
            "messages": [
                {
                    "name": "AppC",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "string",
                            "name": "name",
                            "id": 1
                        },
                        {
                            "rule": "required",
                            "type": "string",
                            "name": "id",
                            "id": 2
                        },
                        {
                            "rule": "optional",
                            "type": "Labels",
                            "name": "labels",
                            "id": 3
                        }
                    ]
                }
            ],
            "enums": [
                {
                    "name": "Type",
                    "values": [
                        {
                            "name": "APPC",
                            "id": 1
                        }
                    ]
                }
            ]
        },
        {
            "name": "Volume",
            "fields": [
                {
                    "rule": "required",
                    "type": "Mode",
                    "name": "mode",
                    "id": 3
                },
                {
                    "rule": "required",
                    "type": "string",
                    "name": "container_path",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "host_path",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "Image",
                    "name": "image",
                    "id": 4
                }
            ],
            "enums": [
                {
                    "name": "Mode",
                    "values": [
                        {
                            "name": "RW",
                            "id": 1
                        },
                        {
                            "name": "RO",
                            "id": 2
                        }
                    ]
                }
            ]
        },
        {
            "name": "ContainerInfo",
            "fields": [
                {
                    "rule": "required",
                    "type": "Type",
                    "name": "type",
                    "id": 1
                },
                {
                    "rule": "repeated",
                    "type": "Volume",
                    "name": "volumes",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "hostname",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "DockerInfo",
                    "name": "docker",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "MesosInfo",
                    "name": "mesos",
                    "id": 5
                }
            ],
            "messages": [
                {
                    "name": "DockerInfo",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "string",
                            "name": "image",
                            "id": 1
                        },
                        {
                            "rule": "optional",
                            "type": "Network",
                            "name": "network",
                            "id": 2,
                            "options": {
                                "default": "HOST"
                            }
                        },
                        {
                            "rule": "repeated",
                            "type": "PortMapping",
                            "name": "port_mappings",
                            "id": 3
                        },
                        {
                            "rule": "optional",
                            "type": "bool",
                            "name": "privileged",
                            "id": 4,
                            "options": {
                                "default": false
                            }
                        },
                        {
                            "rule": "repeated",
                            "type": "Parameter",
                            "name": "parameters",
                            "id": 5
                        },
                        {
                            "rule": "optional",
                            "type": "bool",
                            "name": "force_pull_image",
                            "id": 6
                        }
                    ],
                    "messages": [
                        {
                            "name": "PortMapping",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "uint32",
                                    "name": "host_port",
                                    "id": 1
                                },
                                {
                                    "rule": "required",
                                    "type": "uint32",
                                    "name": "container_port",
                                    "id": 2
                                },
                                {
                                    "rule": "optional",
                                    "type": "string",
                                    "name": "protocol",
                                    "id": 3
                                }
                            ]
                        }
                    ],
                    "enums": [
                        {
                            "name": "Network",
                            "values": [
                                {
                                    "name": "HOST",
                                    "id": 1
                                },
                                {
                                    "name": "BRIDGE",
                                    "id": 2
                                },
                                {
                                    "name": "NONE",
                                    "id": 3
                                }
                            ]
                        }
                    ]
                },
                {
                    "name": "MesosInfo",
                    "fields": [
                        {
                            "rule": "optional",
                            "type": "Image",
                            "name": "image",
                            "id": 1
                        }
                    ]
                }
            ],
            "enums": [
                {
                    "name": "Type",
                    "values": [
                        {
                            "name": "DOCKER",
                            "id": 1
                        },
                        {
                            "name": "MESOS",
                            "id": 2
                        }
                    ]
                }
            ]
        },
        {
            "name": "Labels",
            "fields": [
                {
                    "rule": "repeated",
                    "type": "Label",
                    "name": "labels",
                    "id": 1
                }
            ]
        },
        {
            "name": "Label",
            "fields": [
                {
                    "rule": "required",
                    "type": "string",
                    "name": "key",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "value",
                    "id": 2
                }
            ]
        },
        {
            "name": "Port",
            "fields": [
                {
                    "rule": "required",
                    "type": "uint32",
                    "name": "number",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "name",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "protocol",
                    "id": 3
                }
            ]
        },
        {
            "name": "Ports",
            "fields": [
                {
                    "rule": "repeated",
                    "type": "Port",
                    "name": "ports",
                    "id": 1
                }
            ]
        },
        {
            "name": "DiscoveryInfo",
            "fields": [
                {
                    "rule": "required",
                    "type": "Visibility",
                    "name": "visibility",
                    "id": 1
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "name",
                    "id": 2
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "environment",
                    "id": 3
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "location",
                    "id": 4
                },
                {
                    "rule": "optional",
                    "type": "string",
                    "name": "version",
                    "id": 5
                },
                {
                    "rule": "optional",
                    "type": "Ports",
                    "name": "ports",
                    "id": 6
                },
                {
                    "rule": "optional",
                    "type": "Labels",
                    "name": "labels",
                    "id": 7
                }
            ],
            "enums": [
                {
                    "name": "Visibility",
                    "values": [
                        {
                            "name": "FRAMEWORK",
                            "id": 0
                        },
                        {
                            "name": "CLUSTER",
                            "id": 1
                        },
                        {
                            "name": "EXTERNAL",
                            "id": 2
                        }
                    ]
                }
            ]
        },
        {
            "name": "executor",
            "fields": [],
            "options": {
                "java_package": "org.apache.mesos.v1.executor",
                "java_outer_classname": "Protos"
            },
            "messages": [
                {
                    "name": "Event",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "Type",
                            "name": "type",
                            "id": 1
                        },
                        {
                            "rule": "optional",
                            "type": "Subscribed",
                            "name": "subscribed",
                            "id": 2
                        },
                        {
                            "rule": "optional",
                            "type": "Acknowledged",
                            "name": "acknowledged",
                            "id": 3
                        },
                        {
                            "rule": "optional",
                            "type": "Launch",
                            "name": "launch",
                            "id": 4
                        },
                        {
                            "rule": "optional",
                            "type": "Kill",
                            "name": "kill",
                            "id": 5
                        },
                        {
                            "rule": "optional",
                            "type": "Message",
                            "name": "message",
                            "id": 6
                        },
                        {
                            "rule": "optional",
                            "type": "Error",
                            "name": "error",
                            "id": 7
                        }
                    ],
                    "messages": [
                        {
                            "name": "Subscribed",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "ExecutorInfo",
                                    "name": "executor_info",
                                    "id": 1
                                },
                                {
                                    "rule": "required",
                                    "type": "FrameworkInfo",
                                    "name": "framework_info",
                                    "id": 2
                                },
                                {
                                    "rule": "required",
                                    "type": "AgentInfo",
                                    "name": "agent_info",
                                    "id": 3
                                }
                            ]
                        },
                        {
                            "name": "Launch",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "TaskInfo",
                                    "name": "task",
                                    "id": 1
                                }
                            ]
                        },
                        {
                            "name": "Kill",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "TaskID",
                                    "name": "task_id",
                                    "id": 1
                                }
                            ]
                        },
                        {
                            "name": "Acknowledged",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "TaskID",
                                    "name": "task_id",
                                    "id": 1
                                },
                                {
                                    "rule": "required",
                                    "type": "bytes",
                                    "name": "uuid",
                                    "id": 2
                                }
                            ]
                        },
                        {
                            "name": "Message",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "bytes",
                                    "name": "data",
                                    "id": 1
                                }
                            ]
                        },
                        {
                            "name": "Error",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "string",
                                    "name": "message",
                                    "id": 1
                                }
                            ]
                        }
                    ],
                    "enums": [
                        {
                            "name": "Type",
                            "values": [
                                {
                                    "name": "SUBSCRIBED",
                                    "id": 1
                                },
                                {
                                    "name": "LAUNCH",
                                    "id": 2
                                },
                                {
                                    "name": "KILL",
                                    "id": 3
                                },
                                {
                                    "name": "ACKNOWLEDGED",
                                    "id": 4
                                },
                                {
                                    "name": "MESSAGE",
                                    "id": 5
                                },
                                {
                                    "name": "SHUTDOWN",
                                    "id": 6
                                },
                                {
                                    "name": "ERROR",
                                    "id": 7
                                }
                            ]
                        }
                    ]
                },
                {
                    "name": "Call",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "ExecutorID",
                            "name": "executor_id",
                            "id": 1
                        },
                        {
                            "rule": "required",
                            "type": "FrameworkID",
                            "name": "framework_id",
                            "id": 2
                        },
                        {
                            "rule": "required",
                            "type": "Type",
                            "name": "type",
                            "id": 3
                        },
                        {
                            "rule": "optional",
                            "type": "Subscribe",
                            "name": "subscribe",
                            "id": 4
                        },
                        {
                            "rule": "optional",
                            "type": "Update",
                            "name": "update",
                            "id": 5
                        },
                        {
                            "rule": "optional",
                            "type": "Message",
                            "name": "message",
                            "id": 6
                        }
                    ],
                    "messages": [
                        {
                            "name": "Subscribe",
                            "fields": [
                                {
                                    "rule": "repeated",
                                    "type": "TaskInfo",
                                    "name": "tasks",
                                    "id": 1
                                },
                                {
                                    "rule": "repeated",
                                    "type": "Update",
                                    "name": "updates",
                                    "id": 2
                                }
                            ]
                        },
                        {
                            "name": "Update",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "TaskStatus",
                                    "name": "status",
                                    "id": 1
                                },
                                {
                                    "rule": "required",
                                    "type": "double",
                                    "name": "timestamp",
                                    "id": 2
                                },
                                {
                                    "rule": "required",
                                    "type": "bytes",
                                    "name": "uuid",
                                    "id": 3
                                }
                            ]
                        },
                        {
                            "name": "Message",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "bytes",
                                    "name": "data",
                                    "id": 2
                                }
                            ]
                        }
                    ],
                    "enums": [
                        {
                            "name": "Type",
                            "values": [
                                {
                                    "name": "SUBSCRIBE",
                                    "id": 1
                                },
                                {
                                    "name": "UPDATE",
                                    "id": 2
                                },
                                {
                                    "name": "MESSAGE",
                                    "id": 3
                                }
                            ]
                        }
                    ]
                }
            ]
        },
        {
            "name": "scheduler",
            "fields": [],
            "options": {
                "java_package": "org.apache.mesos.v1.scheduler",
                "java_outer_classname": "Protos"
            },
            "messages": [
                {
                    "name": "Event",
                    "fields": [
                        {
                            "rule": "required",
                            "type": "Type",
                            "name": "type",
                            "id": 1
                        },
                        {
                            "rule": "optional",
                            "type": "Subscribed",
                            "name": "subscribed",
                            "id": 2
                        },
                        {
                            "rule": "optional",
                            "type": "Offers",
                            "name": "offers",
                            "id": 3
                        },
                        {
                            "rule": "optional",
                            "type": "Rescind",
                            "name": "rescind",
                            "id": 4
                        },
                        {
                            "rule": "optional",
                            "type": "Update",
                            "name": "update",
                            "id": 5
                        },
                        {
                            "rule": "optional",
                            "type": "Message",
                            "name": "message",
                            "id": 6
                        },
                        {
                            "rule": "optional",
                            "type": "Failure",
                            "name": "failure",
                            "id": 7
                        },
                        {
                            "rule": "optional",
                            "type": "Error",
                            "name": "error",
                            "id": 8
                        }
                    ],
                    "messages": [
                        {
                            "name": "Subscribed",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "FrameworkID",
                                    "name": "framework_id",
                                    "id": 1
                                },
                                {
                                    "rule": "optional",
                                    "type": "double",
                                    "name": "heartbeat_interval_seconds",
                                    "id": 2
                                }
                            ]
                        },
                        {
                            "name": "Offers",
                            "fields": [
                                {
                                    "rule": "repeated",
                                    "type": "Offer",
                                    "name": "offers",
                                    "id": 1
                                },
                                {
                                    "rule": "repeated",
                                    "type": "InverseOffer",
                                    "name": "inverse_offers",
                                    "id": 2
                                }
                            ]
                        },
                        {
                            "name": "Rescind",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "OfferID",
                                    "name": "offer_id",
                                    "id": 1
                                }
                            ]
                        },
                        {
                            "name": "Update",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "TaskStatus",
                                    "name": "status",
                                    "id": 1
                                }
                            ]
                        },
                        {
                            "name": "Message",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "AgentID",
                                    "name": "agent_id",
                                    "id": 1
                                },
                                {
                                    "rule": "required",
                                    "type": "ExecutorID",
                                    "name": "executor_id",
                                    "id": 2
                                },
                                {
                                    "rule": "required",
                                    "type": "bytes",
                                    "name": "data",
                                    "id": 3
                                }
                            ]
                        },
                        {
                            "name": "Failure",
                            "fields": [
                                {
                                    "rule": "optional",
                                    "type": "AgentID",
                                    "name": "agent_id",
                                    "id": 1
                                },
                                {
                                    "rule": "optional",
                                    "type": "ExecutorID",
                                    "name": "executor_id",
                                    "id": 2
                                },
                                {
                                    "rule": "optional",
                                    "type": "int32",
                                    "name": "status",
                                    "id": 3
                                }
                            ]
                        },
                        {
                            "name": "Error",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "string",
                                    "name": "message",
                                    "id": 1
                                }
                            ]
                        }
                    ],
                    "enums": [
                        {
                            "name": "Type",
                            "values": [
                                {
                                    "name": "SUBSCRIBED",
                                    "id": 1
                                },
                                {
                                    "name": "OFFERS",
                                    "id": 2
                                },
                                {
                                    "name": "RESCIND",
                                    "id": 3
                                },
                                {
                                    "name": "UPDATE",
                                    "id": 4
                                },
                                {
                                    "name": "MESSAGE",
                                    "id": 5
                                },
                                {
                                    "name": "FAILURE",
                                    "id": 6
                                },
                                {
                                    "name": "ERROR",
                                    "id": 7
                                },
                                {
                                    "name": "HEARTBEAT",
                                    "id": 8
                                }
                            ]
                        }
                    ]
                },
                {
                    "name": "Call",
                    "fields": [
                        {
                            "rule": "optional",
                            "type": "FrameworkID",
                            "name": "framework_id",
                            "id": 1
                        },
                        {
                            "rule": "required",
                            "type": "Type",
                            "name": "type",
                            "id": 2
                        },
                        {
                            "rule": "optional",
                            "type": "Subscribe",
                            "name": "subscribe",
                            "id": 3
                        },
                        {
                            "rule": "optional",
                            "type": "Accept",
                            "name": "accept",
                            "id": 4
                        },
                        {
                            "rule": "optional",
                            "type": "Decline",
                            "name": "decline",
                            "id": 5
                        },
                        {
                            "rule": "optional",
                            "type": "Kill",
                            "name": "kill",
                            "id": 6
                        },
                        {
                            "rule": "optional",
                            "type": "Shutdown",
                            "name": "shutdown",
                            "id": 7
                        },
                        {
                            "rule": "optional",
                            "type": "Acknowledge",
                            "name": "acknowledge",
                            "id": 8
                        },
                        {
                            "rule": "optional",
                            "type": "Reconcile",
                            "name": "reconcile",
                            "id": 9
                        },
                        {
                            "rule": "optional",
                            "type": "Message",
                            "name": "message",
                            "id": 10
                        },
                        {
                            "rule": "optional",
                            "type": "Request",
                            "name": "request",
                            "id": 11
                        }
                    ],
                    "messages": [
                        {
                            "name": "Subscribe",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "FrameworkInfo",
                                    "name": "framework_info",
                                    "id": 1
                                },
                                {
                                    "rule": "optional",
                                    "type": "bool",
                                    "name": "force",
                                    "id": 2
                                }
                            ]
                        },
                        {
                            "name": "Accept",
                            "fields": [
                                {
                                    "rule": "repeated",
                                    "type": "OfferID",
                                    "name": "offer_ids",
                                    "id": 1
                                },
                                {
                                    "rule": "repeated",
                                    "type": "Offer.Operation",
                                    "name": "operations",
                                    "id": 2
                                },
                                {
                                    "rule": "optional",
                                    "type": "Filters",
                                    "name": "filters",
                                    "id": 3
                                }
                            ]
                        },
                        {
                            "name": "Decline",
                            "fields": [
                                {
                                    "rule": "repeated",
                                    "type": "OfferID",
                                    "name": "offer_ids",
                                    "id": 1
                                },
                                {
                                    "rule": "optional",
                                    "type": "Filters",
                                    "name": "filters",
                                    "id": 2
                                }
                            ]
                        },
                        {
                            "name": "Kill",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "TaskID",
                                    "name": "task_id",
                                    "id": 1
                                },
                                {
                                    "rule": "optional",
                                    "type": "AgentID",
                                    "name": "agent_id",
                                    "id": 2
                                }
                            ]
                        },
                        {
                            "name": "Shutdown",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "ExecutorID",
                                    "name": "executor_id",
                                    "id": 1
                                },
                                {
                                    "rule": "required",
                                    "type": "AgentID",
                                    "name": "agent_id",
                                    "id": 2
                                }
                            ]
                        },
                        {
                            "name": "Acknowledge",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "AgentID",
                                    "name": "agent_id",
                                    "id": 1
                                },
                                {
                                    "rule": "required",
                                    "type": "TaskID",
                                    "name": "task_id",
                                    "id": 2
                                },
                                {
                                    "rule": "required",
                                    "type": "bytes",
                                    "name": "uuid",
                                    "id": 3
                                }
                            ]
                        },
                        {
                            "name": "Reconcile",
                            "fields": [
                                {
                                    "rule": "repeated",
                                    "type": "Task",
                                    "name": "tasks",
                                    "id": 1
                                }
                            ],
                            "messages": [
                                {
                                    "name": "Task",
                                    "fields": [
                                        {
                                            "rule": "required",
                                            "type": "TaskID",
                                            "name": "task_id",
                                            "id": 1
                                        },
                                        {
                                            "rule": "optional",
                                            "type": "AgentID",
                                            "name": "agent_id",
                                            "id": 2
                                        }
                                    ]
                                }
                            ]
                        },
                        {
                            "name": "Message",
                            "fields": [
                                {
                                    "rule": "required",
                                    "type": "AgentID",
                                    "name": "agent_id",
                                    "id": 1
                                },
                                {
                                    "rule": "required",
                                    "type": "ExecutorID",
                                    "name": "executor_id",
                                    "id": 2
                                },
                                {
                                    "rule": "required",
                                    "type": "bytes",
                                    "name": "data",
                                    "id": 3
                                }
                            ]
                        },
                        {
                            "name": "Request",
                            "fields": [
                                {
                                    "rule": "repeated",
                                    "type": "v1.Request",
                                    "name": "requests",
                                    "id": 1
                                }
                            ]
                        }
                    ],
                    "enums": [
                        {
                            "name": "Type",
                            "values": [
                                {
                                    "name": "SUBSCRIBE",
                                    "id": 1
                                },
                                {
                                    "name": "TEARDOWN",
                                    "id": 2
                                },
                                {
                                    "name": "ACCEPT",
                                    "id": 3
                                },
                                {
                                    "name": "DECLINE",
                                    "id": 4
                                },
                                {
                                    "name": "REVIVE",
                                    "id": 5
                                },
                                {
                                    "name": "KILL",
                                    "id": 6
                                },
                                {
                                    "name": "SHUTDOWN",
                                    "id": 7
                                },
                                {
                                    "name": "ACKNOWLEDGE",
                                    "id": 8
                                },
                                {
                                    "name": "RECONCILE",
                                    "id": 9
                                },
                                {
                                    "name": "MESSAGE",
                                    "id": 10
                                },
                                {
                                    "name": "REQUEST",
                                    "id": 11
                                },
                                {
                                    "name": "SUPPRESS",
                                    "id": 12
                                }
                            ]
                        }
                    ]
                }
            ]
        }
    ],
    "enums": [
        {
            "name": "Status",
            "values": [
                {
                    "name": "DRIVER_NOT_STARTED",
                    "id": 1
                },
                {
                    "name": "DRIVER_RUNNING",
                    "id": 2
                },
                {
                    "name": "DRIVER_ABORTED",
                    "id": 3
                },
                {
                    "name": "DRIVER_STOPPED",
                    "id": 4
                }
            ]
        },
        {
            "name": "TaskState",
            "values": [
                {
                    "name": "TASK_STAGING",
                    "id": 6
                },
                {
                    "name": "TASK_STARTING",
                    "id": 0
                },
                {
                    "name": "TASK_RUNNING",
                    "id": 1
                },
                {
                    "name": "TASK_FINISHED",
                    "id": 2
                },
                {
                    "name": "TASK_FAILED",
                    "id": 3
                },
                {
                    "name": "TASK_KILLED",
                    "id": 4
                },
                {
                    "name": "TASK_LOST",
                    "id": 5
                },
                {
                    "name": "TASK_ERROR",
                    "id": 7
                }
            ]
        }
    ]
}).build();