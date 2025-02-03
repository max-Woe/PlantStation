using PlantStationAPI.Models;
namespace PlantStationAPI.DTOs;

public class MeasurementDTO
{
    public int Id { get; set; }
    public float Value { get; set; }
    public int SensorId { get; set; }
    public int SensorIdReference { get; set; }
    public Sensor? Sensor { get; set; }
    public DateTime RecordedAt { get; set; } = DateTime.UtcNow;
    public DateTime CreatedAt { get; set; } = DateTime.UtcNow;
}