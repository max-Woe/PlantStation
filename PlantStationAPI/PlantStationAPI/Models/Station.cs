namespace PlantStationAPI.Models;

public class Station
{
    public int Id { get; set; }
    public string? MacAddress { get; set; }
    public string? Location { get; set; }
    public int SensorsCount { get; set; }
    public DateTime CreatedAt { get; set; }
}