namespace PlantStationAPI.Models;

public class AppException
{
    public int id { get; set; }
    public string? ExceptionMessage { get; set; }
    public DateTime CreatedAt { get; set; }
}