using Microsoft.AspNetCore.Mvc;
using PlantStationAPI.Data;
using PlantStationAPI.Models;


namespace PlantStationAPI.Controllers;
[ApiController]
[Route("api/[controller]/[action]")]
public class SensorController : ControllerBase
{
    private readonly ApiContext _context;

    public SensorController(ApiContext context) 
    { 
        _context = context; 
    }
    
    [HttpPost]
    public JsonResult Create(Sensor sensor)
    {
        if (sensor.Id != 0)
        {
            return new JsonResult(BadRequest("The id of an new entry has to be 0!"));
        }
        
        _context.Sensors.Add(sensor);
        _context.SaveChanges();
        
        return new JsonResult(Ok(sensor));
    }
}