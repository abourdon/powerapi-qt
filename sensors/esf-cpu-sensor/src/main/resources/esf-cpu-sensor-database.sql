CREATE TABLE Processor (
    id INT,
    name VARCHAR(256),
    tdpMax FLOAT,
    voltageMax FLOAT,
    frequencyMax INT,
    CONSTRAINT pkey
        PRIMARY KEY (id),
    CONSTRAINT integrity
        CHECK (
            name IS NOT NULL AND
            tdpMax IS NOT NULL AND
            voltageMax IS NOT NULL AND
            frequencyMax IS NOT NULL
        ),
    CONSTRAINT onliest
        UNIQUE (name)
);

CREATE TABLE ProcessorVoltage(
    processor INT,
    frequency INT,
    voltage FLOAT,
    CONSTRAINT pkey
        PRIMARY KEY (processor, frequency),
    CONSTRAINT fkeyProcessor
        FOREIGN KEY (processor) REFERENCES Processor(id) ON DELETE CASCADE
);
