using Microsoft.AspNetCore.Mvc;
using PlantStationAPI.Models;

namespace PlantStationAPI.Data;
[ApiController]
[Route("api/[controller]/[action]")]
public class MeasurementController : Controller
{
    private readonly ApiContext _context;

    public MeasurementController(ApiContext context) 
    { 
        _context = context; 
    }

    [HttpPost]
    public JsonResult Create(Measurement measurement)
    {
        if (measurement.Id != 0)
        {
            return new JsonResult(BadRequest("The id of an new entry has to be 0!"));
        }
        
        _context.Measurements.Add(measurement);
        _context.SaveChanges();
        
        return new JsonResult(Ok(measurement));
    }
}