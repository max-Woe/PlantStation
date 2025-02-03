using Microsoft.AspNetCore.Mvc;
using PlantStationAPI.Data;
using PlantStationAPI.Models;


namespace PlantStationAPI.Controllers;
[ApiController]
[Route("api/[controller]/[action]")]
public class StationController : ControllerBase
{
    private readonly ApiContext _context;

    public StationController(ApiContext context) 
    { 
        _context = context; 
    }
    
    [HttpPost]
    public JsonResult Create(Station station)
    {
        if (station.Id != 0)
        {
            return new JsonResult(BadRequest("The id of an new entry has to be 0!"));
        }
        
        _context.Stations.Add(station);
        _context.SaveChanges();
        
        return new JsonResult(Ok(station));
    }
}