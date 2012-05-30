CREATE TABLE NIC (
    id INT,
    vendorId INT,
    deviceId INT,
    type VARCHAR(8),
    name VARCHAR(256),
    CONSTRAINT pkey
        PRIMARY KEY (id),
    CONSTRAINT onliest
        UNIQUE (vendorId, deviceId),
    CONSTRAINT integrity
        CHECK (
            name IS NOT NULL AND
            type IN ('ethernet', 'wireless')
        )
);

CREATE TABLE NICPower (
    nicId INT,
    linkState VARCHAR(256),
    powerConsumption FLOAT,
    CONSTRAINT pkey
        PRIMARY KEY (nicId, linkState),
    CONSTRAINT integrity
        CHECK (
            linkState IS NOT NULL AND
            powerConsumption IS NOT NULL
        )
);

INSERT INTO NIC (id, vendorId, deviceId, type, name)
VALUES (1, 0x8086, 0x10ea, 'ethernet', 'Intel 82577LM Gigabit LAN Driver');

INSERT INTO NICPower (nicId, linkState, powerConsumption)
VALUES (1, '1000Mbs active', 0.627);

INSERT INTO NICPower (nicId, linkState, powerConsumption)
VALUES (1, '100Mbs active', 0.340);

INSERT INTO NICPower (nicId, linkState, powerConsumption)
VALUES (1, '10Mbs active', 0.408);

INSERT INTO NICPower (nicId, linkState, powerConsumption)
VALUES (1, '1000Mbs idle', 0.516);

INSERT INTO NICPower (nicId, linkState, powerConsumption)
VALUES (1, '100Mbs idle', 0.234);

INSERT INTO NICPower (nicId, linkState, powerConsumption)
VALUES (1, '10Mbs idle', 0.206);

INSERT INTO NICPower (nicId, linkState, powerConsumption)
VALUES (1, 'Disconnected cable', 0.026);

INSERT INTO NICPower (nicId, linkState, powerConsumption)
VALUES (1, 'Disconnected LAN', 0.014);
