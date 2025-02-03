using Microsoft.AspNetCore.Mvc;
using PlantStationAPI.Data;
using PlantStationAPI.Models;


namespace PlantStationAPI.Controllers;
[ApiController]
[Route("api/[controller]/[action]")]
public class MeasurementController : ControllerBase
{
    private readonly ApiContext _context;

    public MeasurementController(ApiContext context) 
    { 
        _context = context; 
    }

    [HttpPost]
    public JsonResult Create(Measurement measurement)
    {
        if (measurement == null)
        {
            return new JsonResult(BadRequest("measurment can not be null!"));
        }
            
        if (measurement.Id != 0)
        {
            return new JsonResult(BadRequest("The id of an new entry has to be 0!"));
        }
        
        var sensor = _context.Sensors.Find(measurement.SensorId);
        if (sensor == null)
        {
            return new JsonResult(BadRequest($"Measurement can not be stored. No sensor with the ID: {measurement.SensorId} found."));
        }
        //
        // var station = _context.Stations.Find(measurement.Sensor.StationId);
        // if (station == null)
        // {
        //     return new JsonResult(BadRequest(
        //         $"Measurement can not be stored. No sensor with the ID: {measurement.Sensor.StationId} found."));
        // }
        _context.Measurements.Add(measurement);
        _context.SaveChanges();
        
        return new JsonResult(Ok(measurement));
    }

    [HttpGet]
    public JsonResult Get(int id)
    {
        var result = _context.Measurements.Find(id);

        if (result == null)
        {
            return new JsonResult(NotFound());
        }

        return new JsonResult(Ok(result));
    }
}