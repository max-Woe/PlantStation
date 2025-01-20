namespace PlantStationAPI.Models;

public class Measurement
{
    public int Id { get; set; }
    public float Value { get; set; }
    public int SensorId { get; set; }
    public int SensorIdReference { get; set; }
    public Sensor? Sensor { get; set; }
    public DateTime RecordedAt { get; set; }
    public DateTime CreatedAt { get; set; }
}