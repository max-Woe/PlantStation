﻿namespace PlantStationAPI.Models;

public class Sensor
{
    public int Id { get; set; }
    public string? Type { get; set; }
    public string? Unit { get; set; }
    public int StationId { get; set; }
    public Station? Station { get; set; }
    public DateTime CreatedAt { get; set; }
}