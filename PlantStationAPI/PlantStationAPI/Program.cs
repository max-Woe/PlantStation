using PlantStationAPI.Data;
using Microsoft.EntityFrameworkCore;

var builder = WebApplication.CreateBuilder(args);

var connection_string = Environment.GetEnvironmentVariable("AWS_CONN_STRING");

// Add services to the container.
builder.Services.AddDbContext<ApiContext>(opt => opt.UseNpgsql(connection_string));

builder.Services.AddControllers();

var app = builder.Build();

// Configure the HTTP request pipeline.

app.UseHttpsRedirection();

app.UseAuthorization();

app.MapControllers();

app.Run();