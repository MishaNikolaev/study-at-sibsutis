using System.ComponentModel.DataAnnotations.Schema;

namespace dz10.Model;

    public class Comment
    {
        public int Id { get; set; }
        public int PostId { get; set; }
        public string? Name { get; set; }
        public string? Email { get; set; }
        public string? Body { get; set; }
    }