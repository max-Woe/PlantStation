using Microsoft.EntityFrameworkCore;
using PlantStationAPI.Models;

namespace PlantStationAPI.Data;

public class ApiContext : DbContext
{
    public DbSet<Measurement> Measurements { get; set; }
    public DbSet<Sensor> Sensors { get; set; }
    public DbSet<Station> Stations { get; set; }
    public DbSet<AppException> AppExceptions { get; set; }
    
    public ApiContext(DbContextOptions<ApiContext> options) 
        : base(options) 
    {

    }
}