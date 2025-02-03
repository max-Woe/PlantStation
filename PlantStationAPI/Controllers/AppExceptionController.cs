using Microsoft.AspNetCore.Mvc;
using PlantStationAPI.Data;
using PlantStationAPI.Models;


namespace PlantStationAPI.Controllers;
[ApiController]
[Route("api/[controller]/[action]")]
public class AppExceptionController : ControllerBase
{
    private readonly ApiContext _context;

    public AppExceptionController(ApiContext context) 
    { 
        _context = context; 
    }
    
    [HttpPost]
    public JsonResult Create(AppException appException)
    {
        if (appException.id != 0)
        {
            return new JsonResult(BadRequest("The id of an new entry has to be 0!"));
        }
        
        _context.AppExceptions.Add(appException);
        _context.SaveChanges();
        
        return new JsonResult(Ok(appException));
    }
}